using System.IdentityModel.Tokens.Jwt;
using Microsoft.AspNetCore.Mvc;
using Moq;
using Microsoft.Extensions.Configuration;
using WebApi.Models;
using WebApi.Services;

namespace AuthTest
{
    public class AuthControllerTests
    {
        private readonly Mock<IConfiguration> _mockConfig;
        private readonly Mock<IAuthService> _mockAuthService;
        private readonly AuthController _controller;

        public AuthControllerTests()
        {
            _mockConfig = new Mock<IConfiguration>();
            // Mocking configuration settings as expected by your AuthController
            _mockConfig.Setup(c => c["Jwt:Key"]).Returns("your_secret_key_here");
            _mockConfig.Setup(c => c["Jwt:Issuer"]).Returns("your_issuer");
            _mockConfig.Setup(c => c["Jwt:Audience"]).Returns("your_audience");
            _mockConfig.Setup(c => c["Jwt:Subject"]).Returns("your_subject");

            _mockAuthService = new Mock<IAuthService>();
             // Initialize the AuthController with mocked dependencies
            _controller = new AuthController(_mockConfig.Object, _mockAuthService.Object);
        }

        [Fact]
        public async Task Login_ReturnsOkObjectResult_WithJwtToken_WhenUserIsValid()
        {
            // Arrange
            var userLoginDto = new UserLoginDTO("testuser", "password");
            var user = new User { Username = "testuser", Role = "User", Email = "test@example.com", Age = 30 };
            _mockAuthService.Setup(x => x.ValidateUser(It.IsAny<string>(), It.IsAny<string>())).ReturnsAsync(user);

            // Act
            var result = await _controller.Login(userLoginDto);

            // Assert
            var okResult = Assert.IsType<OkObjectResult>(result);
            Assert.NotNull(okResult.Value);
            Assert.IsType<string>(okResult.Value);  // Verify that the result is a JWT token
        }

        [Fact]
        public async Task Login_ReturnsBadRequest_WhenUserIsInvalid()
        {
            // Arrange
            var userLoginDto = new UserLoginDTO("wronguser", "wrongpassword");
            _mockAuthService.Setup(x => x.ValidateUser(It.IsAny<string>(), It.IsAny<string>())).Throws(new ArgumentException("Invalid username or password"));

            // Act
            var result = await _controller.Login(userLoginDto);

            // Assert
            var badRequestResult = Assert.IsType<BadRequestObjectResult>(result);
            Assert.Equal("Invalid username or password", badRequestResult.Value);
        }

        [Fact]
        public async void GenerateClaims_ReturnsExpectedNumberOfClaims_ForUser()
        {
            // Arrange
            var userLoginDto = new UserLoginDTO("testuser", "password");
            var user = new User { Username = "testuser", Role = "User", Email = "test@example.com", Age = 30 };
            _mockAuthService.Setup(x => x.ValidateUser(It.IsAny<string>(), It.IsAny<string>())).ReturnsAsync(user);

            // Act
            var result = await _controller.Login(userLoginDto);
            var okResult = Assert.IsType<OkObjectResult>(result);
            var jwt = (string)okResult.Value!;
            List<System.Security.Claims.Claim> claims;
            var tokenHandler = new JwtSecurityTokenHandler();
            var securityToken = (JwtSecurityToken)tokenHandler.ReadToken(jwt);
            claims = securityToken.Claims.ToList();

            foreach (var claim in claims)
            {
                Console.WriteLine($"Claim Type: {claim.Type}, Claim Value: {claim.Value}");
            }

            // Assert
            Assert.Equal(10, claims.Count);  // Validate the expected number of claims
            Assert.Contains(claims, c => c.Type == "Email" && c.Value == "test@example.com");
            Assert.Contains(claims, c => c.Type == "Age" && c.Value == "30");
        }
    }
}