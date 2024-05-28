using Microsoft.AspNetCore.Mvc;
using Moq;
using WebApi.Controllers;
using WebApi.Models;
using WebApi.Services;

namespace unittest_turnering.Controllers;

public class TournamentControllerTests
{
    private readonly Mock<ITournamentService> _mockTournamentService;
    private readonly TournamentController _testController;
    
    public TournamentControllerTests()
    {
        _mockTournamentService = new Mock<ITournamentService>();
        _testController = new TournamentController(_mockTournamentService.Object);
    }
    
    [Fact]
    public async Task CreateTournament_ReturnsOkResult_WhenDataIsValid()
    {
        // Arrange
        var tournamentDto = new TournamentCreationDTO(
            "TestAmericano",
            "Americano",
            2,
            32,
            DateTime.Now,
            "Test description",
            new List<string>
            {
                "Player1", "Player2", "Player3", "Player4", "Player5", "Player6", "Player7", "Player8"
            }
        );

        // Act
        var result = await _testController.PostTournament(tournamentDto);

        // Assert
        Assert.IsType<OkResult>(result);
    }
    
    [Fact]
    public async Task CreateTournament_ReturnsBadRequest_WhenExceptionIsThrown()
    {
        // Arrange
        var tournamentDto = new TournamentCreationDTO(
            "TestAmericano",
            "Americano",
            2,
            32,
            DateTime.Now,
            "Test description",
            new List<string>
            {
                "Player1", "Player2", "Player3", "Player4", "Player5", "Player6", "Player7", "Player8"
            }
        );
        _mockTournamentService.Setup(x => x.AddTournamentAsync(It.IsAny<TournamentCreationDTO>())).Throws(new Exception("Test exception"));
    
        // Act
        IActionResult result = await _testController.PostTournament(tournamentDto);
    
        // Assert
        var badRequestResult = Assert.IsType<BadRequestObjectResult>(result);
        Assert.Equal("Test exception", badRequestResult.Value);
    }
    
    [Fact]
    public async Task AddPlayer_ReturnsOk_WhenPlayerIsAddedSuccessfully()
    {
        // Arrange
        string tournamentID = "1";
        string playerName = "John Doe";
        var players = new List<Player>();
        var tournament = new Tournament(
            "Tournament Name", "Round Robin", 2, 21, DateTime.Now, "Sample description", players);

        _mockTournamentService.Setup(s => s.GetTournamentAsync(tournamentID)).ReturnsAsync(tournament);

        // Act
        var result = await _testController.AddPlayer(tournamentID, playerName);

        // Assert
        var okResult = Assert.IsType<OkObjectResult>(result);
        Assert.NotNull(okResult.Value);
        var player = okResult.Value as Player;
        Assert.Equal(playerName, player?.Name);
    }

    [Fact]
    public async Task AddPlayer_ReturnsBadRequest_WhenTournamentStarted()
    {
        // Arrange
        string tournamentID = "1";
        string playerName = "John Doe";
        var players = new List<Player>();
        var tournament = new Tournament(
            "Tournament Name", "Round Robin", 2, 21, DateTime.Now, "Sample description", players);
        tournament.State = 2;  // Simulating that the tournament has already started

        _mockTournamentService.Setup(s => s.GetTournamentAsync(tournamentID)).ReturnsAsync(tournament);

        // Act
        var result = await _testController.AddPlayer(tournamentID, playerName);

        // Assert
        var badRequestResult = Assert.IsType<BadRequestObjectResult>(result);
        Assert.Equal("Tournament already started", badRequestResult.Value);
    }
    
    [Fact]
    public async Task RemovePlayer_ReturnsOk_WhenPlayerIsSuccessfullyRemoved()
    {
        // Arrange
        string tournamentID = "1";
        string playerName = "John Doe";
        var players = new List<Player> { new Player { Name = playerName } };
        var tournament = new Tournament(
            "Tournament Name", "Elimination", 1, 15, DateTime.Now.AddDays(1), "Description", players);

        _mockTournamentService.Setup(s => s.GetTournamentAsync(tournamentID)).ReturnsAsync(tournament);

        // Act
        var result = await _testController.RemovePlayer(tournamentID, playerName);

        // Assert
        Assert.IsType<OkResult>(result);
    }

    [Fact]
    public async Task RemovePlayer_ReturnsBadRequest_WhenPlayerDoesNotExist()
    {
        // Arrange
        string tournamentID = "1";
        string playerName = "John Doe";
        var players = new List<Player>(); // Player list is empty
        var tournament = new Tournament(
            "Tournament Name", "Elimination", 1, 15, DateTime.Now.AddDays(1), "Description", players);

        _mockTournamentService.Setup(s => s.GetTournamentAsync(tournamentID)).ReturnsAsync(tournament);

        // Act
        var result = await _testController.RemovePlayer(tournamentID, playerName);

        // Assert
        var badRequestResult = Assert.IsType<BadRequestObjectResult>(result);
        Assert.Equal("Player is not in tournament", badRequestResult.Value);
    }
    
    [Fact]
    public async Task RequestNewRound_ReturnsOk_WithNewRoundDetails()
    {
        // Arrange
        string tournamentID = "1";
        var newRound = new Round(1); // Assuming round number 1 for the test
        _mockTournamentService.Setup(s => s.RequestNewRoundAsync(tournamentID)).ReturnsAsync(newRound);

        // Act
        var result = await _testController.RequestNewRound(tournamentID);

        // Assert
        var okResult = Assert.IsType<OkObjectResult>(result);
        Assert.Same(newRound, okResult.Value);
    }


    [Fact]
    public async Task GetScoreboard_ReturnsOk_WithPlayerList()
    {
        // Arrange
        string tournamentID = "1";
        var players = new List<Player> { new Player { Name = "John Doe" } };
        _mockTournamentService.Setup(s => s.GetScoreboardAsync(tournamentID)).ReturnsAsync(players);

        // Act
        var result = await _testController.GetScoreboard(tournamentID);

        // Assert
        var okResult = Assert.IsType<OkObjectResult>(result);
        Assert.Same(players, okResult.Value);
    }

    [Fact]
    public async Task SetScores_ReturnsOk_WhenScoresAreSet()
    {
        // Arrange
        string tournamentID = "1";
        var round = new Round(1); // Initialize with round number 1
        _mockTournamentService.Setup(s => s.SetScoresAsync(tournamentID, round)).Returns(Task.CompletedTask);

        // Act
        var result = await _testController.SetScores(tournamentID, round);

        // Assert
        Assert.IsType<OkResult>(result);
    }
    
    [Fact]
    public async Task GetTournament_ReturnsOk_WithTournamentDetails()
    {
        // Arrange
        string tournamentID = "1";
        var tournament = new Tournament(
            "Tournament Name", "Elimination", 1, 15, DateTime.Now, "Description", new List<Player>());
        _mockTournamentService.Setup(s => s.GetTournamentAsync(tournamentID)).ReturnsAsync(tournament);

        // Act
        var result = await _testController.GetTournament(tournamentID);

        // Assert
        var okResult = Assert.IsType<OkObjectResult>(result);
        Assert.Same(tournament, okResult.Value);
    }

    [Fact]
    public async Task GetTournamentHistory_ReturnsOk_WithListOfTournaments()
    {
        // Arrange
        var tournaments = new List<Tournament> { /* Initialize with sample tournaments */ };
        _mockTournamentService.Setup(s => s.GetTournamentHistoryAsync()).ReturnsAsync(tournaments);

        // Act
        var result = await _testController.GetTournamentHistory();

        // Assert
        var okResult = Assert.IsType<OkObjectResult>(result);
        Assert.Same(tournaments, okResult.Value);
    }

}