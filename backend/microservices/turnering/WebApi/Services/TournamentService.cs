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
        string format;
        List<Player> players = new List<Player>();
        switch (tournamentDTO.TournamentFormat.ToUpper())
        {
            case ("AMERICANO") :
            {
                format = "Americano";
                foreach (var player in tournamentDTO.Players)
                {
                    players.Add(new AmericanoPlayer
                    {
                        Name = player
                    });
                }
                break;
            }
            case ("MEXICANO"):
            {
                format = "Mexicano";
                foreach (var player in tournamentDTO.Players)
                {
                    players.Add(new Player
                    {
                        Name = player
                    });
                }
                break;
            }
            default:
            {
                throw new ArgumentException("Invalid tournament format");
            }
        }

        Tournament tournament = new Tournament(tournamentDTO.Name, format, tournamentDTO.Players.Count,
            tournamentDTO.NumberOfCourts, tournamentDTO.PointsPerMatch, players);
        
        await _tournamentDAO.AddTournamentAsync(tournament);
    }

    public async Task<Round> RequestNewRoundAsync(string tournamentID)
    {
        Tournament tournament = await GetTournamentAsync(tournamentID);
        List<Player> players = await GetScoreboardAsync(tournamentID);
        Round round = tournament.GenerateRound(players);
        tournament.Rounds.Add(round);
        await _tournamentDAO.SaveChangesAsync(tournament);
        return round;
    }



    public async Task<List<Player>> GetScoreboardAsync(string tournamentID)
    {
        return await _tournamentDAO.GetScoreboardAsync(tournamentID);
    }

    public async Task<Tournament> GetTournamentAsync(string tournamentID)
    {
        return await _tournamentDAO.GetTournamentAsync(tournamentID);
    }

    public async Task<List<Tournament>> GetTournamentHistoryAsync()
    {
        return await _tournamentDAO.GetTournamentHistoryAsync();
    }
}