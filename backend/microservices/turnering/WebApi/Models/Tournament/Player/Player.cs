namespace WebApi.Models;

public class Player
{
    public string Name { get; set; }
    public int Wins { get; set; } = 0;
    public int Losses { get; set; } = 0;
    public int Draws { get; set; } = 0;
    public int Points { get; set; } = 0;
    public List<Player> PastTeammates { get; set; } = new List<Player>();
}