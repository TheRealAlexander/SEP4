using Microsoft.AspNetCore.Mvc;
using Moq;
using WebApi.Controllers;
using WebApi.Models;
using WebApi.Services;

namespace turnering_unittest_webapi.Controllers;

public class TournamentControllerTest
{
    private readonly Mock<ITournamentService> _tournamentServiceMock;
    private readonly TournamentController _tournamentController;

    public TournamentControllerTest()
    {
        _tournamentServiceMock = new Mock<ITournamentService>();
        _tournamentController = new TournamentController(_tournamentServiceMock.Object);
    }
    
    [Fact]
    public async Task PostTournament_ReturnsOkResult_WhenDataIsValid()
    {
        // Arrange
        var tournamentDto = new TournamentCreationDTO
        {
            Name = "Test Tournament",
            TournamentFormat = "Americano",
            NumberOfCourts = 2,
            PointsPerMatch = 32,
            Players = new List<string>
            {
                "Player 1", "Player 2", "Player 3", "Player 4", "Player 5", "Player 6", "Player 7", "Player 8"
            }
        };

        // Act
        var result = await _tournamentController.PostTournament(tournament);

        // Assert
        var okResult = Assert.IsType<OkResult>(result);
        _tournamentServiceMock.Verify(x => x.AddTournament(tournament), Times.Once);
    }
}