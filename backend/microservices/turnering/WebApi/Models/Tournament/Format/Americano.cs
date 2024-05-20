using System;
using System.Collections.Generic;
using turnering.Models.Tournament;

namespace WebApi.Models
{
    public class Americano : TournamentFormat
    {
        public string TournamentFormat { get; } = "Americano";
        public Round GenerateRound(List<Player> players, Tournament tournament)
        {
            var round = new Round(tournament.NextRoundNumber++);

            players = tournament.ShufflePlayers();
            players = tournament.SkipPlayers();
            
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