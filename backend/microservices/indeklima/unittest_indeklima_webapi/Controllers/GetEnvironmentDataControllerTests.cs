using Moq;
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
            new SensorData { Id = ObjectId.GenerateNewId().ToString(), Temperature = 25.5, Humidity = 50.0, CO2 = 800.0, 
                TemperatureTimestamp = DateTime.Now, HumidityTimestamp = DateTime.Now, CO2Timestamp = DateTime.Now, HallId  = 1 },
            new SensorData { Id = ObjectId.GenerateNewId().ToString(), Temperature = 26.5, Humidity = 51.0, CO2 = 900.0, 
                TemperatureTimestamp = DateTime.Now, HumidityTimestamp = DateTime.Now, CO2Timestamp = DateTime.Now, HallId  = 1 },
            new SensorData { Id = ObjectId.GenerateNewId().ToString(), Temperature = 27.5, Humidity = 52.0, CO2 = 1000.0, 
                TemperatureTimestamp = DateTime.Now, HumidityTimestamp = DateTime.Now, CO2Timestamp = DateTime.Now, HallId  = 1 }
        };
        _mockSensorDataService.Setup(s => s.GetSensorData(1)).ReturnsAsync(sensorDataList);

        // Act
        var result = await _controller.GetSensorData(1);

        // Assert
        Assert.Equal(sensorDataList, result);
    }

    [Fact]
    public async Task GetSensorData_ReturnsEmptyList_WhenNoDataExists()
    {
        // Arrange
        var sensorDataList = new List<SensorData>();
        _mockSensorDataService.Setup(s => s.GetSensorData(1)).ReturnsAsync(sensorDataList);

        // Act
        var result = await _controller.GetSensorData(1);

        // Assert
        Assert.Empty(result);
    }

    [Fact]
    public async Task GetSensorData_WithLimit_Return3Datapoints()
    {
        // Arrange
        var sensorDataList = new List<SensorData>
        {
            new SensorData { Id = ObjectId.GenerateNewId().ToString(), Temperature = 25.5, Humidity = 50.0, CO2 = 800.0, 
                TemperatureTimestamp = DateTime.Now, HumidityTimestamp = DateTime.Now, CO2Timestamp = DateTime.Now, HallId  = 1 },
            new SensorData { Id = ObjectId.GenerateNewId().ToString(), Temperature = 26.5, Humidity = 51.0, CO2 = 900.0, 
                TemperatureTimestamp = DateTime.Now, HumidityTimestamp = DateTime.Now, CO2Timestamp = DateTime.Now, HallId  = 1 },
            new SensorData { Id = ObjectId.GenerateNewId().ToString(), Temperature = 27.5, Humidity = 52.0, CO2 = 1000.0, 
                TemperatureTimestamp = DateTime.Now, HumidityTimestamp = DateTime.Now, CO2Timestamp = DateTime.Now, HallId  = 1 }
        };
        _mockSensorDataService.Setup(s => s.GetSensorData(1, 3)).ReturnsAsync(sensorDataList);

        // Act
        var result = await _controller.GetSensorData(1, 3);

        // Assert
        Assert.Equal(sensorDataList, result);
    }

    [Fact]
    public async Task GetSensorData_WithLimit_ReturnsEmptyList_WhenNoDataExists()
    {
        // Arrange
        var sensorDataList = new List<SensorData>();
        _mockSensorDataService.Setup(s => s.GetSensorData(1, 3)).ReturnsAsync(sensorDataList);

        // Act
        var result = await _controller.GetSensorData(1, 3);

        // Assert
        Assert.Empty(result);
    }

    [Fact]
    public async Task GetSensorData_WithLimit_ReturnsEmptyList_WhenLimitIsZero()
    {
        // Arrange
        var sensorDataList = new List<SensorData>();
        _mockSensorDataService.Setup(s => s.GetSensorData(1, 0)).ReturnsAsync(sensorDataList);

        // Act
        var result = await _controller.GetSensorData(1, 0);

        // Assert
        Assert.Empty(result);
    }

    [Fact]
    public async Task GetSensorData_WithStartDateAndEndDate_ReturnsListOfSensorData()
    {
        // Arrange
        var sensorDataList = new List<SensorData>
        {
            new SensorData { Id = ObjectId.GenerateNewId().ToString(), Temperature = 25.5, Humidity = 50.0, CO2 = 800.0, 
                TemperatureTimestamp = DateTime.Now, HumidityTimestamp = DateTime.Now, CO2Timestamp = DateTime.Now, HallId  = 1 },
            new SensorData { Id = ObjectId.GenerateNewId().ToString(), Temperature = 26.5, Humidity = 51.0, CO2 = 900.0, 
                TemperatureTimestamp = DateTime.Now, HumidityTimestamp = DateTime.Now, CO2Timestamp = DateTime.Now, HallId  = 1 },
            new SensorData { Id = ObjectId.GenerateNewId().ToString(), Temperature = 27.5, Humidity = 52.0, CO2 = 1000.0, 
                TemperatureTimestamp = DateTime.Now, HumidityTimestamp = DateTime.Now, CO2Timestamp = DateTime.Now, HallId  = 1 }
        };
        _mockSensorDataService.Setup(s => s.GetSensorData(It.IsAny<int>(), It.IsAny<DateTime>(), It.IsAny<DateTime>())).ReturnsAsync(sensorDataList);

        // Act
        var result = await _controller.GetSensorData(1, DateTime.Now.AddDays(-1), DateTime.Now);

        // Assert
        Assert.Equal(sensorDataList, result);
    }

}