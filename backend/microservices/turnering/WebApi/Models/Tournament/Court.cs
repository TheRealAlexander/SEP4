using System;

namespace WebApi.Models
{
    public class Court
    {
        private Player[] teams; // Array to represent teams
        private int[] scores; // Array to represent match scores
        private int totalPoints; // Total points to be played in the match

        public Court(int totalPoints)
        {
            teams = new Player[2]; // 2 teams, each with 2 players
            scores = new int[2]; // Initialize scores to 0
            this.totalPoints = totalPoints;
        }

        public void AddPlayer(Player player)
        {
            // Add player to the first available slot in a team
            for (int i = 0; i < 2; i++)
            {
                if (teams[i] == null)
                {
                    teams[i] = player;
                    return;
                }
            }
        }

        public Player[] GetTeams()
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