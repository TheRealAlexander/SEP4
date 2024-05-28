using MongoDB.Driver;
using WebApi.Models;
using WebApi.DAO;

public class SensorDataDAOTests : IAsyncLifetime
{
    //Preconditions: Database must be running on localhost:27017

    private readonly SensorDataDAO _dao;
    private readonly IMongoDatabase _database;

    public SensorDataDAOTests()
    {
        var conn = "mongodb://localhost:27017";
        var client = new MongoClient(conn);
        _database = client.GetDatabase("BackendTestDB");
        _dao = new SensorDataDAO(new MongoDbContext(conn, "BackendTestDB"));
    }

    public async Task InitializeAsync()
    {
        // Clean up database before tests
        await _database.DropCollectionAsync("SensorDataCollection");
    }

    public Task DisposeAsync()
    {
        // No explicit cleanup needed after tests
        return Task.CompletedTask;
    }

    [Fact]
    public async Task AddSensorDataAsync_ShouldAddData_WhenDataIsUnique()
    {
        // Arrange
        var now = DateTime.UtcNow;
        var sensorData = new SensorData 
        { 
            HallId = 1, 
            Temperature = 25, 
            Humidity = 30, 
            CO2 = 400,
            TemperatureTimestamp = now,
            HumidityTimestamp = now,
            CO2Timestamp = now 
        };

        // Act
        await _dao.AddSensorDataAsync(sensorData);

        // Assert
        var insertedData = await _dao.GetSensorDataAsync(1);
        Assert.NotNull(insertedData);
        Assert.Equal(sensorData.Temperature, insertedData[0].Temperature);
        Assert.Equal(sensorData.Humidity, insertedData[0].Humidity);
        Assert.Equal(sensorData.CO2, insertedData[0].CO2);
    }

    [Fact]
    public async Task AddSensorDataAsync_ShouldThrowException_WhenDuplicateData()
    {
        // Arrange
        var sensorData = new SensorData 
        { 
            HallId = 1,
            Temperature = 25, 
            Humidity = 30, 
            CO2 = 400,
            TemperatureTimestamp = DateTime.UtcNow,
            HumidityTimestamp = DateTime.UtcNow,
            CO2Timestamp = DateTime.UtcNow 
        };
        await _dao.AddSensorDataAsync(sensorData);

        // Act
        async Task act() => await _dao.AddSensorDataAsync(sensorData);

        // Assert
        await Assert.ThrowsAsync<Exception>(act);
    }
    
    [Fact]
    public async Task AddSensorDataAsync_ShouldAddData_WhenDuplicateDataInDifferentHall()
    {
        // Arrange
        var now = DateTime.UtcNow;
        var sensorData1 = new SensorData 
        { 
            HallId = 1,
            Temperature = 25, 
            Humidity = 30, 
            CO2 = 400,
            TemperatureTimestamp = now,
            HumidityTimestamp = now,
            CO2Timestamp = now 
        };
        var sensorData2 = new SensorData 
        { 
            HallId = 2,
            Temperature = 25, 
            Humidity = 30, 
            CO2 = 400,
            TemperatureTimestamp = now,
            HumidityTimestamp = now,
            CO2Timestamp = now 
        };
        await _dao.AddSensorDataAsync(sensorData1);

        // Act
        await _dao.AddSensorDataAsync(sensorData2);

        // Assert
        var insertedData1 = await _dao.GetSensorDataAsync(1);
        var insertedData2 = await _dao.GetSensorDataAsync(2);
        Assert.NotNull(insertedData1);
        Assert.NotNull(insertedData2);
        Assert.Equal(sensorData1.Temperature, insertedData1[0].Temperature);
        Assert.Equal(sensorData1.Humidity, insertedData1[0].Humidity);
        Assert.Equal(sensorData1.CO2, insertedData1[0].CO2);
        Assert.Equal(sensorData2.Temperature, insertedData2[0].Temperature);
        Assert.Equal(sensorData2.Humidity, insertedData2[0].Humidity);
        Assert.Equal(sensorData2.CO2, insertedData2[0].CO2);
    }
}