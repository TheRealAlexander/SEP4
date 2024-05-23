using WebApi.Models;

namespace WebApi.Services;

public interface ITournamentService
{
    Task AddTournamentAsync(TournamentCreationDTO tournamentDTO);
    Task<Round> RequestNewRoundAsync(string tournamentID);
    Task<List<Player>> GetScoreboardAsync(string tournamentID);
    Task<Tournament> GetTournamentAsync(string tournamentID);
    Task<List<Tournament>> GetTournamentHistoryAsync();
}