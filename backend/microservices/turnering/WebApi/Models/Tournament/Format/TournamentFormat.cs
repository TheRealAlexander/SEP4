namespace WebApi.Models;

public abstract class TournamentFormat
{
    public abstract Round GenerateRound(List<Player> players, Tournament tournament);
}