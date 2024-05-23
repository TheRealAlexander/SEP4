using Moq;
using Microsoft.AspNetCore.Mvc;
using WebApi.Controllers;
using WebApi.Models;
using WebApi.Models.Dto;
using WebApi.Services;

public class PostEnvironmentDataControllerTests
{
    private readonly Mock<ISensorDataService> _mockSensorDataService;
    private readonly Mock<ISensorGoalService> _mockSensorGoalService;
    private readonly Mock<IIOTControlService> _mockIotControlService;
    private readonly PostEnvironmentDataController _controller;

    public PostEnvironmentDataControllerTests()
    {
        _mockSensorDataService = new Mock<ISensorDataService>();
        _mockSensorGoalService = new Mock<ISensorGoalService>();
        _mockIotControlService = new Mock<IIOTControlService>();
        _controller = new PostEnvironmentDataController(
            _mockSensorDataService.Object,
            _mockSensorGoalService.Object,
            _mockIotControlService.Object
        );
    }

    [Fact]
    public async Task PostSensorData_ReturnsOkResult_WhenDataIsValid()
    {
        // Arrange
        var currentTime = DateTimeOffset.UtcNow.ToUnixTimeSeconds();
        var sensorDataDto = new IOTSensorDataDto 
        { 
            HallId = 1, 
            Temperature = 25, 
            Humidity = 30, 
            CO2 = 400,
            Temperature_ts = currentTime,
            Humidity_ts = currentTime,
            Co2_ts = currentTime
        };
        var sensorGoal = new SensorGoal { HallId = 1, DesiredTemperature = 22, DesiredHumidity = 50, DesiredCo2 = 600 };

        _mockSensorGoalService.Setup(svc => svc.GetSensorGoalAsync(sensorDataDto.HallId)).ReturnsAsync(sensorGoal);
        _mockSensorDataService.Setup(svc => svc.AddSensorDataAsync(It.IsAny<SensorData>())).Returns(Task.CompletedTask);
        _mockIotControlService.Setup(svc => svc.AreDesiredValuesReached(
                It.IsAny<double>(), It.IsAny<double>(),
                It.IsAny<double>(), It.IsAny<double>(),
                It.IsAny<double>(), It.IsAny<double>()))
            .Returns(false);
        _mockIotControlService.Setup(svc => svc.ShouldWindowOpen(
                It.IsAny<double>(), It.IsAny<double>(),
                It.IsAny<double>(), It.IsAny<double>(),
                It.IsAny<double>(), It.IsAny<double>()))
            .Returns(true);

        // Act
        var result = await _controller.PostSensorData(sensorDataDto);

        // Assert
        var okResult = Assert.IsType<OkObjectResult>(result);
        var response = okResult.Value;

        Assert.NotNull(response);

        var success = (bool)response.GetType().GetProperty("success").GetValue(response);
        var code = (int)response.GetType().GetProperty("code").GetValue(response);
        var hallId = (int)response.GetType().GetProperty("hallId").GetValue(response);
        var openWindow = (bool)response.GetType().GetProperty("openWindow").GetValue(response);

        Assert.True(success);
        Assert.Equal(0, code);
        Assert.Equal(sensorDataDto.HallId, hallId);
        Assert.True(openWindow);
    }

    [Fact]
    public async Task PostSensorData_ReturnsBadRequest_WhenExceptionIsThrown()
    {
        // Arrange
        var currentTime = DateTimeOffset.UtcNow.ToUnixTimeSeconds();
        var sensorDataDto = new IOTSensorDataDto 
        { 
            HallId = 1, 
            Temperature = 25, 
            Humidity = 30, 
            CO2 = 400,
            Temperature_ts = currentTime,
            Humidity_ts = currentTime,
            Co2_ts = currentTime
        };
        _mockSensorDataService.Setup(x => x.AddSensorDataAsync(It.IsAny<SensorData>())).Throws(new Exception("Test exception"));

        // Act
        var result = await _controller.PostSensorData(sensorDataDto);

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
