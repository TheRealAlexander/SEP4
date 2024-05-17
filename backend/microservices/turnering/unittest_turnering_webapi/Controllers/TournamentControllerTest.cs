using Microsoft.AspNetCore.Mvc;
using Moq;
using WebApi.Controllers;
using WebApi.Models;
using WebApi.Services;

namespace unittest_turnering_webapi.Controllers;

public class TournamentControllerTest
{
    private readonly Mock<ITournamentService> _mockTournamentService;
    private readonly TournamentController _testController;
    
    public TournamentControllerTest()
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
            new List<string>
            {
                "Player1", "Player2", "Player3", "Player4", "Player5", "Player6", "Player7", "Player8"
            }
        );

        // Act
        var result = await _testController.PostTournament(tournamentDto);

        // Assert
        Assert.IsType<OkResult>(result); // Verify that the result is an OkResult
    }


    
    [Fact]
    public void CreateTournament_ReturnsBadRequest_WhenExceptionIsThrown()
    {
        // Arrange
        var tournamentDto = new TournamentCreationDTO(
            "TestAmericano",
            "Americano",
            2,
            32,
            new List<string>
            {
                "Player1", "Player2", "Player3", "Player4", "Player5", "Player6", "Player7", "Player8"
            }
        );
        _mockTournamentService.Setup(x => x.AddTournamentAsync(It.IsAny<TournamentCreationDTO>())).Throws(new Exception("Test exception"));
        
        // Act
        var result = _testController.PostTournament(tournamentDto);
        
        // Assert
        var badRequestResult = Assert.IsType<BadRequestObjectResult>(result);
        Assert.Equal("Test exception", badRequestResult.Value);
    }

}