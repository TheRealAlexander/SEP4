using Moq;
using WebApi.DAO;
using WebApi.Models;
using WebApi.Services;

namespace unittest_turnering.Services;

public class TournamentServiceTests
{
    private readonly Mock<ITournamentDAO> _mockTournamentDAO;
    private readonly TournamentService _service;

    public TournamentServiceTests()
    {
        _mockTournamentDAO = new Mock<ITournamentDAO>();
        _service = new TournamentService(_mockTournamentDAO.Object);
    }
    
    [Fact]
    public async Task AddTournamentAsync_CallsDao_WhenTournamentIsValid()
    {
        // Arrange
        var tournamentDTO = new TournamentCreationDTO(
            Name: "New Tournament",
            Format: "Americano",
            NumberOfCourts: 2,
            PointsPerMatch: 21,
            StartTime: DateTime.Now,
            Description: "Sample Tournament",
            Players: new List<string> { "Alice", "Bob" }
        );

        // Act
        await _service.AddTournamentAsync(tournamentDTO);

        // Assert
        _mockTournamentDAO.Verify(dao => dao.AddTournamentAsync(It.IsAny<Tournament>()), Times.Once);
    }

    [Fact]
    public async Task AddTournamentAsync_ThrowsArgumentException_WhenFormatIsInvalid()
    {
        // Arrange
        var tournamentDTO = new TournamentCreationDTO(
            Name: "New Tournament",
            Format: "InvalidFormat",
            NumberOfCourts: 2,
            PointsPerMatch: 21,
            StartTime: DateTime.Now,
            Description: "Sample Tournament",
            Players: new List<string> { "Alice", "Bob" }
        );

        // Act & Assert
        await Assert.ThrowsAsync<ArgumentException>(() => _service.AddTournamentAsync(tournamentDTO));
    }
    
    [Fact]
    public async Task RequestNewRoundAsync_ReturnsNewRound_WhenCalled()
    {
        // Arrange
        string tournamentID = "1";
        var players = new List<Player> {
            new Player { Name = "Alice" },
            new Player { Name = "Bob" },
            new Player { Name = "Charlie" },
            new Player { Name = "David" }
        };
        var tournament = new Tournament("Tournament", "Americano", 1, 21, DateTime.Now, "Description", players);

        _mockTournamentDAO.Setup(dao => dao.GetTournamentAsync(tournamentID)).ReturnsAsync(tournament);
        _mockTournamentDAO.Setup(dao => dao.GetScoreboardAsync(tournamentID)).ReturnsAsync(players);

        // Act
        var round = await _service.RequestNewRoundAsync(tournamentID);

        // Assert
        Assert.NotNull(round);
        _mockTournamentDAO.Verify(dao => dao.SaveChangesAsync(tournament), Times.Once);
    }
    
    [Fact]
    public async Task RequestNewRoundAsync_ThrowsException_WhenInsufficientPlayers()
    {
        // Arrange
        string tournamentID = "1";
        var players = new List<Player> {
            new Player { Name = "Alice" },
            new Player { Name = "Bob" },
            new Player { Name = "Charlie" }  // Only three players, one less than required
        };
        var tournament = new Tournament("Tournament", "Americano", 1, 21, DateTime.Now, "Description", players);

        _mockTournamentDAO.Setup(dao => dao.GetTournamentAsync(tournamentID)).ReturnsAsync(tournament);
        _mockTournamentDAO.Setup(dao => dao.GetScoreboardAsync(tournamentID)).ReturnsAsync(players);

        // Act & Assert
        var ex = await Assert.ThrowsAsync<InvalidOperationException>(() => _service.RequestNewRoundAsync(tournamentID));
        Assert.Equal("Insufficient players to start a new round.", ex.Message);
    }

    [Fact]
    public async Task SetScoresAsync_UpdatesScoresCorrectly()
    {
        // Arrange
        string tournamentID = "1";
        var round = new Round(1);
        var rounds = new List<Round> { round }; // Ensure the list contains the round
        var players = new List<Player> { new Player { Name = "Alice" }, new Player { Name = "Bob" } };
        var tournament = new Tournament("Tournament", "Americano", 1, 21, DateTime.Now, "Description", players) { Rounds = rounds };

        _mockTournamentDAO.Setup(dao => dao.GetTournamentAsync(tournamentID)).ReturnsAsync(tournament);

        // Act
        await _service.SetScoresAsync(tournamentID, round);

        // Assert
        _mockTournamentDAO.Verify(dao => dao.SaveChangesAsync(tournament), Times.Once);
    }

    [Fact]
    public async Task GetTournamentAsync_ReturnsTournament_WhenCalled()
    {
        // Arrange
        string tournamentID = "1";
        var expectedTournament = new Tournament("Tournament", "Americano", 1, 21, DateTime.Now, "Description", new List<Player>());
        _mockTournamentDAO.Setup(dao => dao.GetTournamentAsync(tournamentID)).ReturnsAsync(expectedTournament);

        // Act
        var tournament = await _service.GetTournamentAsync(tournamentID);

        // Assert
        Assert.Equal(expectedTournament, tournament);
    }

    [Fact]
    public async Task GetScoreboardAsync_ReturnsPlayers_WhenCalled()
    {
        // Arrange
        string tournamentID = "1";
        var expectedPlayers = new List<Player> { new Player { Name = "Alice" }, new Player { Name = "Bob" } };
        _mockTournamentDAO.Setup(dao => dao.GetScoreboardAsync(tournamentID)).ReturnsAsync(expectedPlayers);

        // Act
        var players = await _service.GetScoreboardAsync(tournamentID);

        // Assert
        Assert.Equal(expectedPlayers, players);
    }
    
}