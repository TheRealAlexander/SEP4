using WebApi.Models;

namespace WebApi.DAO;

public interface ITournamentDAO
{
    Task AddTournamentAsync(Tournament tournament);
    Task<Tournament> GetTournamentAsync(int tournamentID);
    Task<List<Player>> GetScoreboardAsync(int tournamentID);
}