using turnering.Models.Tournament;

namespace WebApi.Models;

public interface TournamentFormat
{
    public string TournamentFormat { get; }
    public Round GenerateRound(List<Player> players, Tournament tournament);
}