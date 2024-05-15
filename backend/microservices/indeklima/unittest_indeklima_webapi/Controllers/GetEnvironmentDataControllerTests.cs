using Xunit;
using Moq;
using Microsoft.AspNetCore.Mvc;
using System.Collections.Generic;
using System.Threading.Tasks;
using MongoDB.Bson;
using WebApi.Controllers;
using WebApi.Models;
using WebApi.Services;

public class GetEnvironmentDataControllerTests
{
    private readonly Mock<ISensorDataService> _mockSensorDataService;
    private readonly GetEnvironmentDataController _controller;

    public GetEnvironmentDataControllerTests()
    {
        _mockSensorDataService = new Mock<ISensorDataService>();
        _controller = new GetEnvironmentDataController(_mockSensorDataService.Object);
    }

    [Fact]
    public async Task GetSensorData_ReturnsListOfSensorData()
    {
        // Arrange
        var sensorDataList = new List<SensorData>
        {
            new SensorData { Id = ObjectId.GenerateNewId().ToString(), Temperature = 25.5, Humidity = 50.0, CO2 = 800.0, Timestamp = DateTime.Now },
            new SensorData { Id = ObjectId.GenerateNewId().ToString(), Temperature = 26.5, Humidity = 51.0, CO2 = 900.0, Timestamp = DateTime.Now },
            new SensorData { Id = ObjectId.GenerateNewId().ToString(), Temperature = 27.5, Humidity = 52.0, CO2 = 1000.0, Timestamp = DateTime.Now }
        };
        _mockSensorDataService.Setup(s => s.GetSensorData()).ReturnsAsync(sensorDataList);

        // Act
        var result = await _controller.GetSensorData();

        // Assert
        Assert.Equal(sensorDataList, result);
    }

    [Fact]
    public async Task GetSensorData_ReturnsEmptyList_WhenNoDataExists()
    {
        // Arrange
        var sensorDataList = new List<SensorData>();
        _mockSensorDataService.Setup(s => s.GetSensorData()).ReturnsAsync(sensorDataList);

        // Act
        var result = await _controller.GetSensorData();

        // Assert
        Assert.Empty(result);
    }
}