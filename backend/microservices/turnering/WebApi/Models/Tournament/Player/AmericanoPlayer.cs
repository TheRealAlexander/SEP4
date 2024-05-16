namespace WebApi.Models;

public class AmericanoPlayer : Player
{
    public List<AmericanoPlayer> PastTeammates { get; set; } = new List<AmericanoPlayer>();
}