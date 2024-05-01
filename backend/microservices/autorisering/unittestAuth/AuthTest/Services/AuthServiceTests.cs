namespace AuthTest;

using Xunit;
using Moq;
using System.Threading.Tasks;
using WebApi.Models;
using WebApi.DAO;
using WebApi.Services;
using System;

public class AuthServiceTests
{
    private readonly AuthService _authService;
    private readonly Mock<IUserDAO> _mockUserDao;

    public AuthServiceTests()
    {
        // Create a mock instance of IUserDAO
        _mockUserDao = new Mock<IUserDAO>();
        
        // Create instance of AuthService with the mocked DAO
        _authService = new AuthService(_mockUserDao.Object);
    }

    [Fact]
    public async Task RegisterUser_ShouldCallRegisterUserAsync_WhenUserIsValid()
    {
        // Arrange
        var userCreationDTO = new UserCreationDTO("username", "password", "email@example.com", "User", 25);
        
        // Setup the mock to return a completed task (success scenario)
        _mockUserDao.Setup(x => x.RegisterUserAsync(It.IsAny<User>()))
                    .Returns(Task.CompletedTask);

        // Act
        await _authService.RegisterUser(userCreationDTO);

        // Assert
        _mockUserDao.Verify(x => x.RegisterUserAsync(It.Is<User>(u =>
            u.Username == "username" &&
            u.Password == "password" &&
            u.Email == "email@example.com")),
            Times.Once);
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
        var result = await _authService.ValidateUser("username", "password");

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
        await Assert.ThrowsAsync<UnauthorizedAccessException>(() => _authService.ValidateUser("username", "wrongpassword"));
    }
}
