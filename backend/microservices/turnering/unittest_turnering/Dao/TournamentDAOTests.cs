using MongoDB.Driver;
using WebApi.DAO;
using WebApi.Models;

namespace unittest_turnering.Dao;

public class TournamentDAOTests : IAsyncLifetime
{
    private readonly TournamentDAO _dao;
    private readonly IMongoDatabase _database;

    public TournamentDAOTests()
    {
        var connectionString = "mongodb://localhost:27017";
        var client = new MongoClient(connectionString);
        _database = client.GetDatabase("TournamentTestDB");
        _dao = new TournamentDAO(new MongoDbContext(connectionString, "TournamentTestDB"));
    }

    public async Task InitializeAsync()
    {
        await _database.DropCollectionAsync("Tournament");
    }

    public Task DisposeAsync()
    {
        // No explicit cleanup needed after tests
        return Task.CompletedTask;
    }

    [Fact]
    public async Task AddTournamentAsync_ShouldInsertTournamentCorrectly()
    {
        // Arrange
        var tournament = new Tournament(
            "Champions League",
            "Americano",
            4,
            21,
            DateTime.UtcNow,
            "Top level competition",
            new List<Player> { new Player { Name = "Alice" }, new Player { Name = "Bob" } }
        );

        // Act
        await _dao.AddTournamentAsync(tournament);

        // Assert
        var insertedTournament = await _dao.GetTournamentAsync(tournament.Id); // Use DAO's own method to fetch
        Assert.NotNull(insertedTournament);
        Assert.Equal(tournament.Name, insertedTournament.Name);
        Assert.Equal(tournament.Players.Count, insertedTournament.Players.Count);
    }

    [Fact]
    public async Task GetTournamentAsync_ReturnsTournament_WhenExists()
    {
        // Arrange
        var tournament = new Tournament(
            "World Cup",
            "Mexicano",
            6,
            15,
            DateTime.UtcNow,
            "International event",
            new List<Player> { new Player { Name = "Carlos" }, new Player { Name = "Maria" } }
        );
        await _dao.AddTournamentAsync(tournament);

        // Act
        var retrievedTournament = await _dao.GetTournamentAsync(tournament.Id);

        // Assert
        Assert.NotNull(retrievedTournament);
        Assert.Equal(tournament.Name, retrievedTournament.Name);
        Assert.Equal(tournament.Players.Count, retrievedTournament.Players.Count);
    }

    [Fact]
    public async Task SaveChangesAsync_UpdatesTournamentCorrectly()
    {
        // Arrange
        var tournament = new Tournament(
            "Open Tournament",
            "Americano",
            2,
            11,
            DateTime.UtcNow,
            "Regional event",
            new List<Player> { new Player { Name = "Alice" }, new Player { Name = "Bob" } }
        );
        await _dao.AddTournamentAsync(tournament);
        tournament.Name = "Updated Open Tournament";
        tournament.Players.Add(new Player { Name = "Charlie" });

        // Act
        await _dao.SaveChangesAsync(tournament);

        // Assert
        var updatedTournament = await _dao.GetTournamentAsync(tournament.Id);
        Assert.Equal("Updated Open Tournament", updatedTournament.Name);
        Assert.Equal(3, updatedTournament.Players.Count);
    }

    [Fact]
    public async Task GetTournamentHistoryAsync_ReturnsAllTournaments()
    {
        // Arrange
        var tournament1 = new Tournament(
            "Tournament One",
            "Americano",
            2,
            11,
            DateTime.UtcNow,
            "Description One",
            new List<Player> { new Player { Name = "Player1" } }
        );
        var tournament2 = new Tournament(
            "Tournament Two",
            "Mexicano",
            3,
            15,
            DateTime.UtcNow,
            "Description Two",
            new List<Player> { new Player { Name = "Player2" } }
        );
        await _dao.AddTournamentAsync(tournament1);
        await _dao.AddTournamentAsync(tournament2);

        // Act
        var tournaments = await _dao.GetTournamentHistoryAsync();

        // Assert
        Assert.Equal(2, tournaments.Count);
        Assert.Contains(tournaments, t => t.Name == "Tournament One");
        Assert.Contains(tournaments, t => t.Name == "Tournament Two");
    }

}