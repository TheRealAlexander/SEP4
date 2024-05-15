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
            tournamentDTO.NumberOfCourts, tournamentDTO.PointsPerMatch, tournamentDTO.Players);
        
        await _tournamentDAO.AddTournamentAsync(tournament);
    }

    public async Task<Tournament> GetTournamentAsync(int tournamentID)
    {
        return await _tournamentDAO.GetTournamentAsync(tournamentID);
    }

    public async Task<Round> RequestNewRoundAsync(int tournamentID)
    {
        Tournament tournament = await GetTournamentAsync(tournamentID);
        Round round = tournament.Format.GenerateRound(tournament.Players, tournament);
        return round;
    }



    public async Task<List<Player>> GetScoreboardAsync(int tournamentID)
    {
        Tournament tournament = await GetTournamentAsync(tournamentID);
        var players = tournament.Players;
        players.Sort((player1, player2) => player2.Points.CompareTo(player1.Points));
        return players;
    }
}