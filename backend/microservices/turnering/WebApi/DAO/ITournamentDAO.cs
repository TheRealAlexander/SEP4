using turnering.Models.Tournament;
using WebApi.Models;

namespace WebApi.DAO;

public interface ITournamentDAO
{
    Task AddTournamentAsync(Tournament tournament);
    Task<Tournament> GetTournamentAsync(string tournamentID);
    Task<List<Player>> GetScoreboardAsync(string tournamentID);
    Task<List<TournamentWithFormatAsStringDto>> GetTournamentHistoryAsync();
}