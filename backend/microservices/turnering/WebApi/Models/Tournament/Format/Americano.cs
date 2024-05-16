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

            ShufflePlayers(players);
            
            for (int i = 0; i < tournament.NumberOfCourts; i++)
            {
                round.Courts.Add(new Court(tournament.PointsPerMatch));
            }

            foreach (Court court in round.Courts)
            {
                for (int i = 0; i < 2; i++)
                {
                    court.AddPlayer(players[0]);
                    for (int j = 1; j < players.Count - 1; j++)
                    {
                        if (!((AmericanoPlayer)players[0]).PastTeammates.Contains(players[j]))
                        {
                            court.AddPlayer(players[j]);
                            players.RemoveAt(j);
                            break;
                        }
                    }
                    players.RemoveAt(0);
                }
            }
            return round;
        }
    }
}