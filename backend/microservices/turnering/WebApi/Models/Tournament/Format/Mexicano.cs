using System;
using System.Collections.Generic;

namespace WebApi.Models
{
    public class Mexicano : TournamentFormat
    {
        public override Round GenerateRound(List<Player> players, Tournament tournament)
        {
            var round = new Round();
    
            if (tournament.FirstRound)
            {
                ShufflePlayers(players);
                tournament.FirstRound = false;
            }

            var court = new Court(tournament.PointsPerMatch);
            for (int i = 0; i < players.Count; i += 4)
            {
                court.AddPlayer(players[i]);
                court.AddPlayer(players[i + 2]);
                court.AddPlayer(players[i + 1]);
                court.AddPlayer(players[i + 3]);
                round.Courts.Add(court);
                court = new Court(tournament.PointsPerMatch);
            }

            return round;
        }


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
    }
}