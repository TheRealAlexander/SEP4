namespace WebApi.Models;

public record TournamentCreationDTO(string Name, string TournamentFormat, int NumberOfCourts, int PointsPerMatch, List<string> Players, List<Player> SkippedARound);