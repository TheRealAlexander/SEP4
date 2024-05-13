using Microsoft.AspNetCore.Mvc;
using WebApi.Models;
using WebApi.Services;

namespace WebApi.Controllers;

[ApiController]
[Route("api/[controller]")]
public class PostTournamentController : ControllerBase
{
    private ITournamentService _tournamentService;
    
    public PostTournamentController(ITournamentService tournamentService)
    {
        _tournamentService = tournamentService;
    }
    
    [HttpPost]
    public async Task<IActionResult> PostTournament([FromBody] Tournament tournament)
    {
        await _tournamentService.AddTournament(tournament);
        return Ok();
    }
}