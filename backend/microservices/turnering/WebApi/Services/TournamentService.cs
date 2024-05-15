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

    public async Task AddTournamentAsync(TournamentCreationDTO tournamentDTO)
    {
        TournamentFormat format;
        switch (tournamentDTO.TournamentFormat)
        {
            case ("Americano") :
            {
                format = new Americano();
                break;
            }
            case ("Mexicano"):
            {
                format = new Mexicano();
                break;
            }
            default:
            {
                throw new ArgumentException("Invalid tournament type");
            }
        }

        Tournament tournament = new Tournament(tournamentDTO.Name, format, tournamentDTO.Players.Count,
            tournamentDTO.NumberOfCourts, tournamentDTO.Players);
        
        await _tournamentDAO.AddTournamentAsync(tournament);
    }
}