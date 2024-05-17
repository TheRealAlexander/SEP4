using Moq;
using Microsoft.AspNetCore.Mvc;
using WebApi.Controllers;
using WebApi.Models;
using WebApi.Services;

public class PostEnvironmentDataGoalControllerTests
{
    private readonly Mock<ISensorGoalService> _mockSensorGoalService;
    private readonly PostEnvironmentDataGoalController _controller;

    public PostEnvironmentDataGoalControllerTests()
    {
        _mockSensorGoalService = new Mock<ISensorGoalService>();
        _controller = new PostEnvironmentDataGoalController(_mockSensorGoalService.Object);
    }

    [Fact]
    public async Task PostSensorDataGoal_ReturnsOkResult_WhenDataIsValid()
    {
        // Arrange
        var sensorGoal = new SensorGoal
        {
            HallId = 1,
            DesiredTemperature = 22,
            DesiredHumidity = 50,
            DesiredCo2 = 600
        };

        _mockSensorGoalService.Setup(svc => svc.AddOrUpdateSensorGoalAsync(sensorGoal))
            .Returns(Task.CompletedTask);

        // Act
        var result = await _controller.PostSensorDataGoal(sensorGoal);

        // Assert
        var okResult = Assert.IsType<OkObjectResult>(result);
        var response = okResult.Value;

        Assert.NotNull(response);

        var success = (bool)response.GetType().GetProperty("success").GetValue(response);
        var hallId = (int)response.GetType().GetProperty("hallId").GetValue(response);
        var desiredTemperature = (double)response.GetType().GetProperty("desiredTemperature").GetValue(response);
        var desiredHumidity = (double)response.GetType().GetProperty("desiredHumidity").GetValue(response);
        var desiredCo2 = (double)response.GetType().GetProperty("desiredCo2").GetValue(response);

        Assert.True(success);
        Assert.Equal(sensorGoal.HallId, hallId);
        Assert.Equal(sensorGoal.DesiredTemperature, desiredTemperature);
        Assert.Equal(sensorGoal.DesiredHumidity, desiredHumidity);
        Assert.Equal(sensorGoal.DesiredCo2, desiredCo2);
    }

    [Fact]
    public async Task PostSensorDataGoal_ReturnsBadRequest_WhenExceptionIsThrown()
    {
        // Arrange
        var sensorGoal = new SensorGoal
        {
            HallId = 1,
            DesiredTemperature = 22,
            DesiredHumidity = 50,
            DesiredCo2 = 600
        };

        _mockSensorGoalService.Setup(svc => svc.AddOrUpdateSensorGoalAsync(sensorGoal))
            .ThrowsAsync(new Exception("Test exception"));

        // Act
        var result = await _controller.PostSensorDataGoal(sensorGoal);

        // Assert
        var badRequestResult = Assert.IsType<BadRequestObjectResult>(result);
        var response = badRequestResult.Value;

        Assert.NotNull(response);

        var success = (bool)response.GetType().GetProperty("success").GetValue(response);
        var error = (string)response.GetType().GetProperty("error").GetValue(response);

        Assert.False(success);
        Assert.Equal("Test exception", error);
    }
}
