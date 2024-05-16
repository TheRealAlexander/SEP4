using MongoDB.Driver;
using WebApi.Models;
using WebApi.DAO;

public class SensorDataDAOTests : IAsyncLifetime
{
    //Preconditions: 

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
        var sensorData = new SensorData { Temperature = 25, Humidity = 30, Timestamp = DateTime.UtcNow };

        // Act
        await _dao.AddSensorDataAsync(sensorData);

        // Assert
        var insertedData = await _dao.GetSensorDataAsync();
        Assert.NotNull(insertedData);
        Assert.Equal(sensorData.Temperature, insertedData[0].Temperature);
        Assert.Equal(sensorData.Humidity, insertedData[0].Humidity);
    }

    [Fact]
    public async Task AddSensorDataAsync_ShouldThrowExeption_WhenDuplicateData()
    {
        //Arrange
        var sensorData = new SensorData { Temperature = 25, Humidity = 30, Timestamp = DateTime.UtcNow };
        await _dao.AddSensorDataAsync(sensorData);

        //Act
        async Task act() => await _dao.AddSensorDataAsync(sensorData);

        //Assert
        await Assert.ThrowsAsync<Exception>(act);
        
    }
}