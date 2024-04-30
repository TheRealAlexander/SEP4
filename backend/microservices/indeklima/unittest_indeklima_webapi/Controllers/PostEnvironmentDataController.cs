using Xunit;
using Moq;
using Microsoft.AspNetCore.Mvc;
using System;
using WebApi.Controllers;
using WebApi.Models;
using WebApi.Models.Dto;
using WebApi.Services;

public class PostEnviromentDataControllerTests
{
    private readonly Mock<ISensorDataService> _mockSensorDataService;
    private readonly PostEnviromentDataController _controller;

    public PostEnviromentDataControllerTests()
    {
        _mockSensorDataService = new Mock<ISensorDataService>();
        _controller = new PostEnviromentDataController(_mockSensorDataService.Object);
    }

    [Fact]
    public void PostSensorData_ReturnsOkResult_WhenDataIsValid()
    {
        // Arrange
        var sensorDataDto = new IOTSensorDataDto { Temperature = 25, Humidity = 30 };

        // Act
        var result = _controller.PostSensorData(sensorDataDto);

        // Assert
        var okResult = Assert.IsType<OkObjectResult>(result);
        Assert.Equal(0, okResult.Value);
    }

    [Fact]
    public void PostSensorData_ReturnsBadRequest_WhenExceptionIsThrown()
    {
        // Arrange
        var sensorDataDto = new IOTSensorDataDto { Temperature = 25, Humidity = 30 };
        _mockSensorDataService.Setup(x => x.AddSensorData(It.IsAny<SensorData>())).Throws(new Exception("Test exception"));

        // Act
        var result = _controller.PostSensorData(sensorDataDto);

        // Assert
        var badRequestResult = Assert.IsType<BadRequestObjectResult>(result);
        Assert.Equal("Test exception", badRequestResult.Value);
    }
}