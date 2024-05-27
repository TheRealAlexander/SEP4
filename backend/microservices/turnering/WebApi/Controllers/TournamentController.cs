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
        try
        {
            await _tournamentService.AddTournamentAsync(tournamentCreationDto);
            return Ok();
        }
        catch (Exception e)
        {
            return BadRequest(e.Message);
        }
    }

    [HttpPost("{tournamentID}/players")]
    public async Task<IActionResult> AddPlayer([FromRoute] string tournamentID, [FromBody] string playerName)
    {
        Tournament tournament = await _tournamentService.GetTournamentAsync(tournamentID);
        if (tournament.State != 1)
        {
            return BadRequest("Tournament already started");
        }

        foreach (Player player in tournament.Players)
        {
            if (player.Name.Equals(playerName))
            {
                return BadRequest("Player is already in tournament");
            }
        }

        Player newPlayer = new Player { Name = playerName };
        
        tournament.Players.Add(newPlayer);
        await _tournamentService.SaveChangesAsync(tournament);
        return Ok(newPlayer);
    }

    [HttpDelete("{tournamentID}/players/{playerName}")]
    public async Task<IActionResult> RemovePlayer([FromRoute] string tournamentID, [FromRoute] string playerName)
    {
        Tournament tournament = await _tournamentService.GetTournamentAsync(tournamentID);
        if (tournament.State != 1)
        {
            return BadRequest("Tournament already started");
        }

        foreach (Player player in tournament.Players)
        {
            if (player.Name.Equals(playerName))
            {
                tournament.Players.Remove(player);
                await _tournamentService.SaveChangesAsync(tournament);
                return Ok();
            }
        }

        return BadRequest("Player is not in tournament");
    }

    [HttpPost("/{tournamentID}/newRound")]
    public async Task<IActionResult> RequestNewRound([FromRoute] string tournamentID)
    {
        Round newRound = await _tournamentService.RequestNewRoundAsync(tournamentID);
        return Ok(newRound);
    }
    
    [HttpGet("{tournamentID}/scoreboard")]
    public async Task<IActionResult> GetScoreboard([FromRoute] string tournamentID)
    {
        List<Player> players = await _tournamentService.GetScoreboardAsync(tournamentID);
        return Ok(players);
    }

    [HttpPost("{tournamentID}/points")]
    public async Task<IActionResult> SetScores([FromRoute] string tournamentID, [FromBody] Round round)
    {
        await _tournamentService.SetScoresAsync(tournamentID, round);
        return Ok();
    }

    [HttpGet("{tournamentID}")]
    public async Task<IActionResult> GetTournament([FromRoute] string tournamentID)
    {
        Tournament tournament = await _tournamentService.GetTournamentAsync(tournamentID);
        return Ok(tournament);
    }

    [HttpGet("history")]
    public async Task<IActionResult> GetTournamentHistory()
    {
        List<Tournament> tournaments = await _tournamentService.GetTournamentHistoryAsync();
        return Ok(tournaments);
    }
}