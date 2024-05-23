using System.ComponentModel.DataAnnotations;

namespace AuthTest;

using Xunit;
using Moq;
using System.Threading.Tasks;
using WebApi.Models;
using WebApi.DAO;
using WebApi.Services;
using System;

public class UserServiceTests
{
    private readonly UserService _userService;
    private readonly Mock<IUserDAO> _mockUserDao;

    public UserServiceTests()
    {
        // Create a mock instance of IUserDAO
        _mockUserDao = new Mock<IUserDAO>();
        
        // Create instance of UserService with the mocked DAO
        _userService = new UserService(_mockUserDao.Object);
    }

    [Fact]
    public async Task RegisterUser_ShouldCallRegisterUserAsync_WhenUserIsValid()
    {
        // Arrange
        var userCreationDTO = new UserCreationDTO("username", "password", "email@example.com", 25);
        
        // Setup the mock to return a completed task (success scenario)
        _mockUserDao.Setup(x => x.RegisterUserAsync(It.IsAny<User>()))
                    .Returns(Task.CompletedTask);

        // Act
        await _userService.RegisterUserAsync(userCreationDTO);

        // Assert
        _mockUserDao.Verify(x => x.RegisterUserAsync(It.Is<User>(u =>
            u.Username == "username" &&
            u.Password == "password" &&
            u.Email == "email@example.com")),
            Times.Once);
    }
    
    [Fact]
    public async Task RegisterUser_ShouldThrowValidationException_WhenPasswordIsLessThan8Characters()
    {
	    // Arrange
	    var userCreationDTO = new UserCreationDTO("username", "short", "email@example.com", 25);

	    // Act & Assert
	    var exception = await Assert.ThrowsAsync<ValidationException>(() => _userService.RegisterUserAsync(userCreationDTO));
	    Assert.Equal("Password must be at least 8 characters long.", exception.Message);
    }

    [Fact]
    public async Task ValidateUser_ShouldReturnUser_WhenCredentialsAreCorrect()
    {
        // Arrange
        var expectedUser = new User
        {
            Username = "username",
            Password = "password",
            Email = "email@example.com"
        };

        _mockUserDao.Setup(x => x.ValidateUserAsync("username", "password"))
                    .ReturnsAsync(expectedUser);

        // Act
        var result = await _userService.ValidateUserAsync("username", "password");

        // Assert
        Assert.Equal(expectedUser, result);
    }

    [Fact]
    public async Task ValidateUser_ShouldThrow_WhenPasswordIsIncorrect()
    {
        // Arrange
        _mockUserDao.Setup(x => x.ValidateUserAsync("username", "wrongpassword"))
                    .ThrowsAsync(new UnauthorizedAccessException("Password is incorrect."));

        // Act & Assert
        await Assert.ThrowsAsync<UnauthorizedAccessException>(() => _userService.ValidateUserAsync("username", "wrongpassword"));
    }
	[Fact]
	public async Task GetAllUsersAsync_GroupsUsersByRole()
	{
    	// Arrange
    	var users = new List<User>
    	{
       	 new User { Username = "admin1", Password = "pass", Email = "admin1@test.com", Role = "Admin", Age = 24 },
         new User { Username = "superuser1", Password = "pass", Email = "superuser1@test.com", Role = "SuperUser", Age = 25 },
         new User { Username = "user1", Password = "pass", Email = "user1@test.com", Role = "User", Age = 26 }
   	 };
    	_mockUserDao.Setup(x => x.GetAllUsersAsync()).ReturnsAsync(users);

    	// Act
    	var result = await _userService.GetAllUsersAsync();
	
	    // Assert
    	Assert.Equal(3, result.Count);
    	Assert.All(result, sublist => Assert.NotEmpty(sublist)); // Check that all sublists are not empty
    	Assert.True(result.Any(group => group.Any(u => u.Role == "Admin")));
    	Assert.True(result.Any(group => group.Any(u => u.Role == "SuperUser")));
    	Assert.True(result.Any(group => group.Any(u => u.Role == "User")));
	}


}
