using WebApi.DAO;
using WebApi.Models;

namespace WebApi.Services;

public class TournamentService : ITournamentService
{
    private readonly ITournamentDAO _tournamentDAO;

    public TournamentService(ITournamentDAO tournamentDAO)
    {
        _tournamentDAO = tournamentDAO;
    }

    public async Task AddTournament(Tournament tournament)
    {
        await _tournamentDAO.AddTournamentAsync(tournament);
    }
}