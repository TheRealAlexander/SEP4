using Microsoft.AspNetCore.Mvc;
using WebApi.Models;
using WebApi.Services;

namespace WebApi.Controllers;

[ApiController]
[Route("[controller]")]
public class TournamentController : ControllerBase
{
    private ITournamentService _tournamentService;
    
    public TournamentController(ITournamentService tournamentService)
    {
        _tournamentService = tournamentService;
    }
    
    [HttpPost]
    public async Task<IActionResult> PostTournament([FromBody] TournamentCreationDTO tournamentCreationDto)
    {
        await _tournamentService.AddTournamentAsync(tournamentCreationDto);
        return Ok();
    }

    [HttpPost("/{tournamentID}/newRound")]
    public async Task<IActionResult> RequestNewRound([FromRoute] string tournamentID)
    {
        Round newRound = await _tournamentService.RequestNewRoundAsync(tournamentID);
        return Ok(newRound);
    }

    [HttpGet("{tournamentID}")]
    public async Task<IActionResult> GetScoreboard([FromRoute] string tournamentID)
    {
        List<Player> players = await _tournamentService.GetScoreboardAsync(tournamentID);
        return Ok(players);
    }
}