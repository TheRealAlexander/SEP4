using System.ComponentModel.DataAnnotations;
using WebApi.DAO;
using WebApi.Models;
using System.Data;

namespace WebApi.Services
{
   public class UserService : IUserService
{

    private readonly IUserDAO _userDAO;

    public UserService(IUserDAO userDAO)
    {
        _userDAO = userDAO;
    }

    public async Task<User> ValidateUserAsync(string username, string password)
    {
        try
        {
            User existingUser = await _userDAO.ValidateUserAsync(username, password);
            if (existingUser == null)
            {
                throw new UnauthorizedAccessException("Username or password is incorrect.");
            }
            return existingUser;
        }
        catch (UnauthorizedAccessException)
        {
            // Re-throw specific exceptions directly without wrapping
            throw;
        }
        catch (Exception ex)
        {
            // For unexpected errors, you might still want to wrap to add context or log them appropriately
            throw new Exception("An error occurred during user validation.", ex);
        }
    }

    public async Task<User> GetUserAsync(string username)
    {
        return await _userDAO.GetUserAsync(username); 
    }

    public async Task RegisterUserAsync(UserCreationDTO userCreationDTO)
    {
        if (string.IsNullOrEmpty(userCreationDTO.Username) || string.IsNullOrEmpty(userCreationDTO.Password) || string.IsNullOrEmpty(userCreationDTO.Email))
        {
            throw new ValidationException("Username, password, and email cannot be null or empty.");
        }

        // Check for the uniqueness of the username and register the user
        try
        {
            var user = new User
            {
                Username = userCreationDTO.Username,
                Password = userCreationDTO.Password,
                Email = userCreationDTO.Email,
                Role = "User",
                Age = userCreationDTO.Age
            };

            await _userDAO.RegisterUserAsync(user);
        }
        catch (DuplicateNameException ex)
        {
            // Rethrow this specific exception to be caught by the controller
            throw ex;
        }
        catch (Exception ex)
        {
            throw new Exception("Failed to register user: " + ex.Message, ex);
        }
    }

    public async Task<List<List<User>>> GetAllUsersAsync()
    {
        try
        {
            List<User> adminList = new List<User>();
            List<User> superUserList = new List<User>();
            List<User> userList = new List<User>();
            List<List<User>> allUsersList = new List<List<User>>();

            foreach (User user in await _userDAO.GetAllUsersAsync())
            {
                if (user.Role == "Admin")
                {
                    adminList.Add(user);
                } else if (user.Role == "SuperUser")
                {
                    superUserList.Add(user);
                }
                else
                {
                    userList.Add(user);
                }
            }
            
            allUsersList.Add(adminList);
            allUsersList.Add(superUserList);
            allUsersList.Add(userList);

            return allUsersList;
        }
        catch (Exception ex)
        {
            throw new Exception($"Failed to retrieve all users sorted by role: {ex.Message}", ex);
        }
    }

    public async Task<User> UpdateUserAsync(User user)
    {
        return await _userDAO.UpdateUserAsync(user);
    }

}
}
