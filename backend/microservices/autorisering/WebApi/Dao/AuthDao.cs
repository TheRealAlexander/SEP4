using MongoDB.Driver;
using WebApi.DAO;

namespace WebApi.Dao
{
    public class AuthDao : IAuthDao
    {
        private readonly IMongoCollection<User> _authDataMongoCollection;

        public AuthDao(MongoDbContext context)
        {
            _authDataMongoCollection = context.Database.GetCollection<User>("AuthData");
        }


        public Task<User> ValidateUser(string username, string password) {
            //TODO: Implement this method
            throw new NotImplementedException();
        }
        public Task<User> GetUser(string username, string password) {
            //TODO: Implement this method
            throw new NotImplementedException();
        }

        public Task RegisterUser(User user) {
            //TODO: Implement this method
            throw new NotImplementedException();

        }
        
    }
}