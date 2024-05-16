using System;

namespace WebApi.Models
{
    public class Court
    {
        private Player[][] teams;
        private int[] scores;
        private int totalPoints;

        public Court(int totalPoints)
        {
            teams = new Player[2][];
            scores = new int[2];
            this.totalPoints = totalPoints;
        }

        public void AddPlayer(Player player)
        {
            for (int i = 0; i < 2; i++)
            {
                for (int j = 0; j < 2; j++)
                {
                    if (teams[i][j] == null)
                    {
                        teams[i][j] = player;
                        return;
                    }
                }
            }
        }

        public Player[][] GetTeams()
        {
            return teams;
        }

        public void SetScore(int team1Score)
        {
            int team2Score = totalPoints - team1Score;
            scores[0] = team1Score;
            scores[1] = team2Score;
        }

        public int[] GetScores()
        {
            return scores;
        }
    }
}