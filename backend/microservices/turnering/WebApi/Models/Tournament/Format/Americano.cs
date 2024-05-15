using System;
using System.Collections.Generic;

namespace WebApi.Models
{
    public class Americano : TournamentFormat
    {
        private void ShufflePlayers(List<Player> players)
        {
            Random rng = new Random();
            int n = players.Count;
            while (n > 1)
            {
                n--;
                int k = rng.Next(n + 1);
                Player value = players[k];
                players[k] = players[n];
                players[n] = value;
            }
        }

        public override Round GenerateRound(List<Player> players, Tournament tournament)
        {
            var round = new Round();
            var playersPerRound = players.Count / 2;
            
            ShufflePlayers(players);

            for (var j = 0; j < playersPerRound; j++)
            {
                var player1 = players[j];
                var player2 = players[playersPerRound + j];

                var court = new Court(tournament.PointsPerMatch);
                court.AddPlayer(player1);
                court.AddPlayer(player2);

                round.Courts.Add(court);
            }

            return round;
        }
    }
}