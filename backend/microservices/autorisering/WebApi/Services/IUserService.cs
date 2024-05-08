using WebApi.Models;

namespace WebApi.Services
{
    public interface IUserService {

        Task<User> ValidateUserAsync(string username, string password);
        Task<User> GetUserAsync(string username);
        Task RegisterUserAsync(UserCreationDTO userCreationDTO);
        Task<List<List<User>>> GetAllUsersAsync();
        Task<User> UpdateUserAsync(User user);

    } 
}
