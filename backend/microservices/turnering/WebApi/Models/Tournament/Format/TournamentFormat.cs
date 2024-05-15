namespace WebApi.Models;

public abstract class TournamentFormat
{
    public abstract void GenerateRound(List<Player> players); // TODO Needs to return Round object
}