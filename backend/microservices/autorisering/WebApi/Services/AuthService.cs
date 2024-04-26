using System.ComponentModel.DataAnnotations;

public class AuthService : IAuthService
{

    private readonly IUserDAO _userDAO;

    public AuthService(IUserDAO userDAO)
    {
        _userDAO = userDAO;
    }

    public async Task<User> ValidateUser(string username, string password)
    {
        try
        {
            // Use UserDAO to validate the user asynchronously
            User existingUser = await _userDAO.ValidateUserAsync(username, password);

            if (existingUser == null)
            {
                // If no user is returned, it means the user was not found or the password didn't match
                throw new Exception("Username or password is incorrect.");
            }

            // If a user is found and the password matches, return the user object
            return existingUser;
        }
        catch (Exception ex)
        {
            throw new Exception("An error occurred during user validation.", ex);
        }
    }


    public async Task<User> GetUser(string username)
    {
        return await _userDAO.GetUserAsync(username);
    }

    public async Task RegisterUser(UserCreationDTO userCreationDTO)
    {
        if (string.IsNullOrEmpty(userCreationDTO.Username))
        {
            throw new ValidationException("Username cannot be null or empty.");
        }

        if (string.IsNullOrEmpty(userCreationDTO.Password))
        {
            throw new ValidationException("Password cannot be null or empty.");
        }

        if (string.IsNullOrEmpty(userCreationDTO.Email))
        {
            throw new ValidationException("Email cannot be null or empty.");
        }

        // Check for the uniqueness of the username and register the user
        try
        {
            var user = new User
            {
                Username = userCreationDTO.Username,
                Password = userCreationDTO.Password,
                Email = userCreationDTO.Email,
                Role = userCreationDTO.Role,
                Age = userCreationDTO.Age
            };
            
            await _userDAO.RegisterUserAsync(user);
        }
        catch (Exception ex)
        {
            throw new Exception("Failed to register user: " + ex.Message, ex);
        }
    }
}