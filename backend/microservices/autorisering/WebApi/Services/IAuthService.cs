public interface IAuthService {

    Task<User> ValidateUser(string username, string password);
    // Task<User> GetUser(string username, string password);
    // Task RegisterUser(User user);

}