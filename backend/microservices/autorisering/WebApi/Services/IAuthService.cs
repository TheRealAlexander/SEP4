using WebApi.Models;

namespace WebApi.Services
{
    public interface IAuthService {

        Task<User> ValidateUserAsync(string username, string password);
        Task<User> GetUserAsync(string username);
        Task RegisterUserAsync(UserCreationDTO userCreationDTO);
        Task<List<User>> GetAllUsersAsync();
        Task<User> UpdateUserAsync(User user);

    } 
}
