using System.ComponentModel.DataAnnotations;

public class AuthService : IAuthService
{

    private readonly IList<User> users = new List<User>
    {
        new User
        {
            Age = 36,
            Email = "trmo@via.dk",
            Password = "onetwo3FOUR",
            Role = "Teacher",
            Username = "trmo",
        },
        new User
        {
            Age = 34,
            Email = "jakob@gmail.com",
            Password = "password",
            Role = "Student",
            Username = "jknr",
        },
        new User 
        {
            Age = 23,
            Email = "331458@viauc.dk",
            Password = "private",
            Role = "Admin",
            Username = "Brugge"
        }
    };

    public Task<User> ValidateUser(string username, string password)
    {
        User? existingUser = users.FirstOrDefault(u => 
            u.Username.Equals(username, StringComparison.OrdinalIgnoreCase));
        
        if (existingUser == null)
        {
            throw new Exception("User not found");
        }

        if (!existingUser.Password.Equals(password))
        {
            throw new Exception("Password mismatch");
        }

        return Task.FromResult(existingUser);
    }

    // public Task RegisterUser(User user)
    // {

    //     if (string.IsNullOrEmpty(user.Username))
    //     {
    //         throw new ValidationException("Username cannot be null");
    //     }

    //     if (string.IsNullOrEmpty(user.Password))
    //     {
    //         throw new ValidationException("Password cannot be null");
    //     }
    //     // Do more user info validation here
        
    //     // save to persistence instead of list
        
    //     users.Add(user);
        
    //     return Task.CompletedTask;
    // }
}