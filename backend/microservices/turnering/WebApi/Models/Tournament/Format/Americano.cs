namespace WebApi.Models
{
    public class Americano : TournamentFormat
    {
        public static Round GenerateRound(List<Player> players, Tournament tournament)
        {
            var round = new Round(tournament.Rounds.Count + 1);

            tournament.ShufflePlayers();
            players = tournament.SkipPlayers();
            
            for (int i = 0; i < tournament.NumberOfCourts; i++)
            {
                Court court = new Court(tournament.PointsPerMatch);
                for (int j = 0; j < 2; j++)
                {
                    court.AddPlayer(players[0]);
                    for (int k = 1; k < players.Count - 1; k++)
                    {
                        if (!players[0].PastTeammates.Contains(players[j]))
                        {
                            court.AddPlayer(players[j]);
                            players.RemoveAt(j);
                            break;
                        }
                    }
                    players.RemoveAt(0);
                }
                round.Courts.Add(court);
            }
            return round;
        }
    }
}