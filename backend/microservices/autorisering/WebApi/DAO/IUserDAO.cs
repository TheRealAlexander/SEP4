using WebApi.Models;

namespace WebApi.DAO;

public interface IUserDAO {
    Task<User> GetUserAsync(string username);
    Task RegisterUserAsync(User user);
    Task<User> ValidateUserAsync(string username, string password);
}