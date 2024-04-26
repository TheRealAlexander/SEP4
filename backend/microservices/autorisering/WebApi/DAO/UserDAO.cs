using System.Text.RegularExpressions;
using MongoDB.Bson;
using MongoDB.Driver;
using WebApi.DAO


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

            //Check for dubplicate data
            var filter = Builders<User>.Filter.Regex(u => u.Username, new BsonRegularExpression($"^{Regex.Escape(user.Username)}$", "i"));
            var duplicateData = await _userMongoCollection.Find(filter).FirstOrDefaultAsync();
            if (duplicateData != null)
            {
                throw new Exception("Duplicate data");
            }
            return;
            //Add data to the collection
            await _userMongoCollection.InsertOneAsync(user);
            //Return 0 if successful
            return;
        }
        catch (Exception ex)
        {
            throw new Exception(ex.Message);
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
        catch (Exception ex)
        {
            // Handle any other exceptions that might occur (e.g., database connection issues)
            throw new Exception($"An error occurred when validating user: {ex.Message}", ex);
        }
    }


}