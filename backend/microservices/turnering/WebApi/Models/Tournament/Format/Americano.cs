using System;
using System.Collections.Generic;

namespace WebApi.Models
{
    public class Americano : TournamentFormat
    {
        public override void GenerateRound(List<Player> players)
        {
            Random random = new Random();
            for (int i = players.Count - 1; i > 0; i--)
            {
                int j = random.Next(0, i + 1);
                Player temp = players[i];
                players[i] = players[j];
                players[j] = temp;
            }
            
            int courtCount = (int)Math.Ceiling((double)players.Count / 4);
            for (int i = 0; i < courtCount; i++)
            {
                int startIndex = i * 4;
                int remainingPlayers = Math.Min(4, players.Count - startIndex);
                List<Player> courtPlayers = players.GetRange(startIndex, remainingPlayers);
            }
        }
    }
}