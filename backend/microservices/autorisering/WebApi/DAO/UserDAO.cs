using System.Text.RegularExpressions;
using MongoDB.Bson;
using MongoDB.Driver;
using WebApi.DAO;
using WebApi.Models;
using System.Data;


public class UserDAO : IUserDAO
{
    private readonly IMongoCollection<User> _userMongoCollection;

    public UserDAO(MongoDbContext context)
    {
        _userMongoCollection = context.Database.GetCollection<User>("UserData");
    }

    public async Task<User> GetUserAsync(string username)
    {
        try
        {
            // Use a regular expression with case-insensitive search
            var filter = Builders<User>.Filter.Regex(u => u.Username, new BsonRegularExpression(username, "i"));
            var user = await _userMongoCollection.Find(filter).FirstOrDefaultAsync();

            if (user == null)
            {
                throw new KeyNotFoundException($"User with username {username} not found.");
            }

            return user;
        }
        catch (Exception ex)
        {
            throw new Exception($"An error occurred when retrieving user: {ex.Message}", ex);
        }
    }


    public async Task RegisterUserAsync(User user)
    {
        try
        {
            if (user == null)
            {
                throw new ArgumentNullException(nameof(user));
            }

            // Check for duplicate data
            var filter = Builders<User>.Filter.Regex(u => u.Username, new BsonRegularExpression($"^{Regex.Escape(user.Username)}$", "i"));
            var duplicateData = await _userMongoCollection.Find(filter).FirstOrDefaultAsync();
            if (duplicateData != null)
            {
                throw new DuplicateNameException("Username already taken");
            }

            // Add data to the collection
            await _userMongoCollection.InsertOneAsync(user);
        }
        catch (DuplicateNameException)
        {
            // Rethrow this exception directly without additional wrapping
            throw;
        }
        catch (Exception ex)
        {
            throw new Exception("Failed to register user: " + ex.Message, ex);
        }
    }


    public async Task<User> ValidateUserAsync(string username, string password)
    {
        try
        {
            // Attempt to retrieve the user by username (case-insensitive)
            var filter = Builders<User>.Filter.Regex(u => u.Username, new BsonRegularExpression($"^{username}$", "i"));
            var user = await _userMongoCollection.Find(filter).FirstOrDefaultAsync();

            // If no user is found, or the password does not match, throw an exception
            if (user == null)
            {
                throw new UnauthorizedAccessException("Username is incorrect.");
            }

            if (user.Password != password) {
                throw new UnauthorizedAccessException("Password is incorrect.");
            }

            // If user is found and password matches, return the user object
            return user;
        }
        catch (UnauthorizedAccessException)
        {
            // Re-throw specific exceptions to be handled or tested appropriately
            throw;
        }
        catch (Exception ex)
        {
            // Optionally, log and handle unexpected exceptions here, or wrap them if there's a good reason
            throw new Exception($"An unexpected error occurred when validating user: {ex.Message}", ex);
        }
    }

    public async Task<List<User>> GetAllUsersAsync()
    {
        try
        {
            // Define a sort by 'Role' in ascending order
            var sortByRole = Builders<User>.Sort.Ascending(u => u.Role);
        
            // Retrieve all users from the collection and sort them by 'Role'
            return await _userMongoCollection.Find(new BsonDocument()).Sort(sortByRole).ToListAsync();
        }
        catch (Exception ex)
        {
            // Handle or log the exception as needed
            throw new Exception($"Failed to retrieve all users sorted by role: {ex.Message}", ex);
        }
        
    }
    
    public async Task<User> UpdateUserAsync(User user)
	{
   		try
    	{
        	// Create a filter to match the user by username (which remains unchanged)
        	var filter = Builders<User>.Filter.Eq(userData => userData.Username, user.Username);

        	// Create an update definition to set new values for all updatable fields
        	var updateDefinition = Builders<User>.Update
            	.Set(userData => userData.Password, user.Password)
            	.Set(userData => userData.Email, user.Email)
            	.Set(userData => userData.Role, user.Role)
            	.Set(userData => userData.Age, user.Age);  // Add more fields as necessary

        	// Perform the update operation
        	var result = await _userMongoCollection.UpdateOneAsync(filter, updateDefinition);

        	// Check if the update was successful, if not, handle it appropriately
        	if (result.MatchedCount == 0)
            	throw new KeyNotFoundException($"No user found with username {user.Username}");
        	if (result.ModifiedCount == 0)
            	throw new Exception("No changes were made during the update operation.");

        	// Return the updated user data - consider fetching the user again if accurate data is needed
        	return user;
    	}
    	catch (Exception ex)
    	{
        	throw new Exception($"Failed to update user: {ex.Message}", ex);
    	}
	}

    
}