using WebApi.Models;

namespace WebApi.Services;

public interface ITournamentService
{
    Task AddTournamentAsync(TournamentCreationDTO tournamentDTO);
    Task<Tournament> GetTournamentAsync(int tournamentID);
    Task<Round> RequestNewRoundAsync(int tournamentID);
    Task<List<Player>> GetScoreboardAsync(int tournamentID);
}