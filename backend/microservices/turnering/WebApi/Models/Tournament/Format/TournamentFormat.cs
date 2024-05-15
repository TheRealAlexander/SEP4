namespace WebApi.Models;

public abstract class TournamentFormat
{
    public abstract void GenerateRound(List<Player> players);
}