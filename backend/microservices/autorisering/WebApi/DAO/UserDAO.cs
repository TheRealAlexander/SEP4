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



}