using System;
using System.Collections.Generic;
using WebApi.DAO;

namespace WebApi.Models
{
    public class Mexicano : TournamentFormat
    {
        public override Round GenerateRound(List<Player> players, Tournament tournament)
        {
            var round = new Round();
    
            if (tournament.FirstRound)
            {
                players = tournament.ShufflePlayers();
                tournament.FirstRound = false;
            }
            
            players = tournament.SkipPlayers();
            
            for (int i = 0; i < tournament.NumberOfCourts; i++)
            {
                round.Courts.Add(new Court(tournament.PointsPerMatch));
            }

            foreach (Court court in round.Courts)
            {
                court.AddPlayer(players[0]);
                court.AddPlayer(players[2]);
                court.AddPlayer(players[1]);
                court.AddPlayer(players[3]);
                for (int i = 0; i < 4; i++)
                {
                    players.RemoveAt(0);
                }
            }

            return round;
        }
        
    }
}