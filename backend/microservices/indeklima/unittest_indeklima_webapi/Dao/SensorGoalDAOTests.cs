using MongoDB.Driver;
using WebApi.DAO;
using WebApi.Models;

public class SensorGoalDaoTests : IAsyncLifetime
{
    private readonly SensorGoalDAO _dao;
    private readonly IMongoDatabase _database;

    public SensorGoalDaoTests()
    {
        var conn = "mongodb://localhost:27017";
        var client = new MongoClient(conn);
        _database = client.GetDatabase("BackendTestDB");
        _dao = new SensorGoalDAO(new MongoDbContext(conn, "BackendTestDB"));
    }

    public async Task InitializeAsync()
    {
        // Clean up database before tests
        await _database.DropCollectionAsync("SensorGoals");
    }

    public Task DisposeAsync()
    {
        // No explicit cleanup needed after tests
        return Task.CompletedTask;
    }

    [Fact]
    public async Task GetSensorGoalAsync_ReturnsExpectedSensorGoal()
    {
        // Arrange
        var sensorGoal = new SensorGoal { HallId = 1, DesiredTemperature = 22, DesiredHumidity = 50, DesiredCo2 = 600 };
        await _dao.AddOrUpdateSensorGoalAsync(sensorGoal);

        // Act
        var result = await _dao.GetSensorGoalAsync(1);

        // Assert
        Assert.NotNull(result);
        Assert.Equal(sensorGoal.HallId, result.HallId);
        Assert.Equal(sensorGoal.DesiredTemperature, result.DesiredTemperature);
        Assert.Equal(sensorGoal.DesiredHumidity, result.DesiredHumidity);
        Assert.Equal(sensorGoal.DesiredCo2, result.DesiredCo2);
    }

    [Fact]
    public async Task AddOrUpdateSensorGoalAsync_InsertsNewDocument_WhenNoExistingGoal()
    {
        // Arrange
        var sensorGoal = new SensorGoal { HallId = 1, DesiredTemperature = 22, DesiredHumidity = 50, DesiredCo2 = 600 };

        // Act
        await _dao.AddOrUpdateSensorGoalAsync(sensorGoal);

        // Assert
        var result = await _dao.GetSensorGoalAsync(sensorGoal.HallId);
        Assert.NotNull(result);
        Assert.Equal(sensorGoal.HallId, result.HallId);
        Assert.Equal(sensorGoal.DesiredTemperature, result.DesiredTemperature);
        Assert.Equal(sensorGoal.DesiredHumidity, result.DesiredHumidity);
        Assert.Equal(sensorGoal.DesiredCo2, result.DesiredCo2);
    }

    [Fact]
    public async Task AddOrUpdateSensorGoalAsync_UpdatesExistingDocument_WhenGoalExists()
    {
        // Arrange
        var initialGoal = new SensorGoal { HallId = 1, DesiredTemperature = 20, DesiredHumidity = 40, DesiredCo2 = 500 };
        var updatedGoal = new SensorGoal { HallId = 1, DesiredTemperature = 22, DesiredHumidity = 50, DesiredCo2 = 600 };
        await _dao.AddOrUpdateSensorGoalAsync(initialGoal);

        // Act
        await _dao.AddOrUpdateSensorGoalAsync(updatedGoal);

        // Assert
        var result = await _dao.GetSensorGoalAsync(updatedGoal.HallId);
        Assert.NotNull(result);
        Assert.Equal(updatedGoal.HallId, result.HallId);
        Assert.Equal(updatedGoal.DesiredTemperature, result.DesiredTemperature);
        Assert.Equal(updatedGoal.DesiredHumidity, result.DesiredHumidity);
        Assert.Equal(updatedGoal.DesiredCo2, result.DesiredCo2);
    }

    [Fact]
    public async Task DeleteSensorGoalAsync_DeletesDocument_WhenCalled()
    {
        // Arrange
        var sensorGoal = new SensorGoal { HallId = 1, DesiredTemperature = 22, DesiredHumidity = 50, DesiredCo2 = 600 };
        await _dao.AddOrUpdateSensorGoalAsync(sensorGoal);

        // Act
        await _dao.DeleteSensorGoalAsync(sensorGoal.HallId);

        // Assert
        var result = await _dao.GetSensorGoalAsync(sensorGoal.HallId);
        Assert.Null(result);
    }
}
