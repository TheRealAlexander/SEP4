namespace WebApi.Models;

public interface TournamentFormat
{
    public Round GenerateRound(List<Player> players, Tournament tournament);
}