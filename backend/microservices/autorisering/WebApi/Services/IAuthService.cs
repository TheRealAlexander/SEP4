using WebApi.Models;

namespace WebApi.Services
{
    public interface IAuthService {

        Task<User> ValidateUser(string username, string password);
        Task<User> GetUser(string username);
        Task RegisterUser(UserCreationDTO userCreationDTO);

    } 
}
