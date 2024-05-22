namespace WebApi.Models;

public interface TournamentFormat
{
    public static abstract Round GenerateRound(List<Player> players, Tournament tournament);
}