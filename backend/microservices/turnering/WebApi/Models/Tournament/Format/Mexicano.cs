namespace WebApi.Models
{
    public class Mexicano : TournamentFormat
    {
        public static Round GenerateRound(List<Player> players, Tournament tournament)
        {
            var round = new Round(tournament.Rounds.Count + 1);
    
            if (tournament.NextRoundNumber == 1)
            {
                tournament.ShufflePlayers();
            }
            
            players = tournament.SkipPlayers();
            
            for (int i = 0; i < tournament.NumberOfCourts; i++)
            {
                Court court = new Court(tournament.PointsPerMatch);
                court.AddPlayer(players[0]);
                court.AddPlayer(players[2]);
                court.AddPlayer(players[1]);
                court.AddPlayer(players[3]);
                for (int j = 0; j < 4; j++)
                {
                    players.RemoveAt(0);
                }
                round.Courts.Add(court);
            }

            return round;
        }
    }
}