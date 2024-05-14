using Moq;
using WebApi.DAO;
using WebApi.Models;
using WebApi.Services;

namespace unittest_indeklima_webapi.Services;

public class SensorDataServiceTests
{
    private readonly Mock<ISensorDataDAO> _mockSensorDataDao;
    private readonly SensorDataService _service;

    public SensorDataServiceTests()
    {
        _mockSensorDataDao = new Mock<ISensorDataDAO>();
        _service = new SensorDataService(_mockSensorDataDao.Object);
    }

    [Fact]
    public async Task GetSensorData_ReturnsExpectedData()
    {
        // Arrange
        var expectedData = new List<SensorData> { new SensorData(), new SensorData() };
        _mockSensorDataDao.Setup(dao => dao.GetSensorDataAsync()).ReturnsAsync(expectedData);

        // Act
        var result = await _service.GetSensorData();

        // Assert
        Assert.Equal(expectedData, result);
    }

    [Fact]
    public void AddSensorData_ThrowsException_WhenSensorDataIsNull()
    {
        // Arrange
        SensorData sensorData = null;

        // Act & Assert
        Assert.ThrowsAsync<ArgumentNullException>(() => _service.AddSensorData(sensorData));
    }

    [Fact]
    public async Task AddSensorData_CallsDao_WhenSensorDataIsValid()
    {
        // Arrange
        var sensorData = new SensorData();

        // Act
        await _service.AddSensorData(sensorData);

        // Assert
        _mockSensorDataDao.Verify(dao => dao.AddSensorDataAsync(sensorData), Times.Once);
    }
}