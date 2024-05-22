using Microsoft.AspNetCore.Mvc;
using Moq;
using SharedObjects.Models;
using Broker.Services;
using System.Collections.Generic;
using System.Threading.Tasks;
using Xunit;
using Broker.Controllers;

namespace BrokerTest
{
    public class BrokerControllerTests
    {
        private readonly Mock<IBrokerService> _mockBrokerService;
        private readonly BrokerController _controller;

        public BrokerControllerTests()
        {
            _mockBrokerService = new Mock<IBrokerService>();
            _controller = new BrokerController(_mockBrokerService.Object);
        }

        [Fact]
        public async Task GetSensorData_ReturnsOkResult_WhenDataExists()
        {
            // Arrange
            var hallId = 1;
            var sensorDataList = new List<SensorData> { new SensorData { /* initialize properties here */ } };
            _mockBrokerService.Setup(x => x.GetSensorData(hallId)).ReturnsAsync(sensorDataList);

            // Act
            var result = await _controller.GetSensorData(hallId);

            // Assert
            var okResult = Assert.IsType<OkObjectResult>(result.Result);
            Assert.IsType<List<SensorData>>(okResult.Value);
        }

        [Fact]
        public async Task UpdateTournament_ReturnsExpectedResult()
        {
            // Arrange
            var tournamentId = "1";
            var tournamentData = new Tournament { /* initialize properties here */ };
            var updatedTournament = new Tournament { /* initialize properties here */ };
            _mockBrokerService.Setup(x => x.UpdateTournament(tournamentId, tournamentData)).ReturnsAsync(updatedTournament);

            // Act
            var result = await _controller.UpdateTournament(tournamentId, tournamentData);

            // Assert
            var actionResult = Assert.IsType<ActionResult<Tournament>>(result);
            Assert.Equal(updatedTournament, actionResult.Value);
        }

        [Fact]
        public async Task DeleteTournament_ReturnsNoContentResult_WhenSuccessful()
        {
            // Arrange
            var tournamentId = "1";
            _mockBrokerService.Setup(x => x.DeleteTournament(tournamentId)).ReturnsAsync(new NoContentResult());

            // Act
            var result = await _controller.DeleteTournament(tournamentId);

            // Assert
            Assert.IsType<NoContentResult>(result);
        }

        [Fact]
        public async Task AddParticipant_ReturnsExpectedResult()
        {
            // Arrange
            var tournamentId = "1";
            var participant = "participant1";
            _mockBrokerService.Setup(x => x.AddParticipant(tournamentId, participant)).ReturnsAsync(participant);
            // Act
            var result = await _controller.AddParticipant(tournamentId, participant);

            // Assert
            var actionResult = Assert.IsType<ActionResult<string>>(result);
            Assert.Equal(participant, actionResult.Value);
        }

        [Fact]
        public async Task RemoveParticipant_ReturnsNoContentResult_WhenSuccessful()
        {
            // Arrange
            var tournamentId = "1";
            var participant = "participant1";
            _mockBrokerService.Setup(x => x.RemoveParticipant(tournamentId, participant)).ReturnsAsync(new NoContentResult());

            // Act
            var result = await _controller.RemoveParticipant(tournamentId, participant);

            // Assert
            Assert.IsType<NoContentResult>(result);
        }

        [Fact]
        public async Task Login_ReturnsExpectedResult()
        {
            // Arrange
            var user = "testUser";
            var expected = "loginResult";
            _mockBrokerService.Setup(x => x.Login(user)).ReturnsAsync(expected);

            // Act
            var result = await _controller.Login(user);

            // Assert
            var actionResult = Assert.IsType<ActionResult<string>>(result);
            Assert.Equal(expected, actionResult.Value);
        }

        [Fact]
        public async Task FetchSuperUsers_ReturnsExpectedResult()
        {
            // Arrange
            var expected = "superUsersResult";
            _mockBrokerService.Setup(x => x.FetchSuperUsers()).ReturnsAsync(expected);

            // Act
            var result = await _controller.FetchSuperUsers();

            // Assert
            var actionResult = Assert.IsType<ActionResult<string>>(result);
            Assert.Equal(expected, actionResult.Value);
        }

        [Fact]
        public async Task FetchNonAdminUsers_ReturnsExpectedResult()
        {
            // Arrange
            var expected = "nonAdminUsersResult";
            _mockBrokerService.Setup(x => x.FetchNonAdminUsers()).ReturnsAsync(expected);

            // Act
            var result = await _controller.FetchNonAdminUsers();

            // Assert
            var actionResult = Assert.IsType<ActionResult<string>>(result);
            Assert.Equal(expected, actionResult.Value);
        }

        [Fact]
        public async Task AdjustUserPermissions_ReturnsExpectedResult()
        {
            // Arrange
            var usersToChange = "usersToChange";
            var expected = "adjustUserPermissionsResult";
            _mockBrokerService.Setup(x => x.AdjustUserPermissions(usersToChange)).ReturnsAsync(expected);

            // Act
            var result = await _controller.AdjustUserPermissions(usersToChange);

            // Assert
            var actionResult = Assert.IsType<ActionResult<string>>(result);
            Assert.Equal(expected, actionResult.Value);
        }

        [Fact]
        public async Task RegisterUser_ReturnsExpectedResult()
        {
            // Arrange
            var user = "testUser";
            var expected = "registerUserResult";
            _mockBrokerService.Setup(x => x.RegisterUser(user)).ReturnsAsync(expected);

            // Act
            var result = await _controller.RegisterUser(user);

            // Assert
            var actionResult = Assert.IsType<ActionResult<string>>(result);
            Assert.Equal(expected, actionResult.Value);
        }
    }
}