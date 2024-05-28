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
        foreach (var player in tournamentDTO.Players)
        {
            players.Add(new Player
            {
                Name = player
            });
        }
        switch (tournamentDTO.Format.ToUpper())
        {
            case "AMERICANO" : format = "Americano"; break;
            case "MEXICANO" : format = "Mexicano"; break;
            default : throw new ArgumentException("Invalid tournament format");
        }

        Tournament tournament = new Tournament(tournamentDTO.Name, format,
            tournamentDTO.NumberOfCourts, tournamentDTO.PointsPerMatch, tournamentDTO.StartTime, tournamentDTO.Description, players);
        
        await _tournamentDAO.AddTournamentAsync(tournament);
    }

    public async Task<Round> RequestNewRoundAsync(string tournamentID)
    {
        Tournament tournament = await GetTournamentAsync(tournamentID);
        List<Player> players = await GetScoreboardAsync(tournamentID);
        
        if (players.Count < 4)
        {
            throw new InvalidOperationException("Insufficient players to start a new round.");
        }
        else if (players.Count < tournament.NumberOfCourts * 4)
        {
            tournament.NumberOfCourts = players.Count / 4;
        }
        
        Round round = tournament.GenerateRound(players);
        tournament.Rounds.Add(round);
        tournament.State = 2;
        await _tournamentDAO.SaveChangesAsync(tournament);
        return round;
    }

    public async Task SetScoresAsync(string tournamentID, Round round)
    {
        Tournament tournament = await GetTournamentAsync(tournamentID);
        foreach (Court court in round.Courts)
        {
            Player[][] players = court.GetTeams();
            int[] scores = court.GetScores();
            for (int i = 0; i < 2; i++)
            {
                for (int j = 0; j < 2; j++)
                {
                    Player player = tournament.Players.Find(p => p.Name.Equals(players[i][j].Name))!;
                    player.Points += scores[i];
                    if (scores[i] > tournament.PointsPerMatch / 2.0)
                    {
                        player.Wins++;
                    }
                    else if (scores[i] < tournament.PointsPerMatch / 2.0)
                    {
                        player.Losses++;
                    }
                    else
                    {
                        player.Draws++;
                    }
                }
            }
        }

        tournament.Rounds[round.RoundNumber - 1] = round;
        await SaveChangesAsync(tournament);
    }

    public async Task SaveChangesAsync(Tournament tournament)
    {
        await _tournamentDAO.SaveChangesAsync(tournament);
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