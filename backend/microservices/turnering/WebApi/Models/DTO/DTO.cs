namespace WebApi.Models;

public record TournamentCreationDTO(string Name, string TournamentFormat, int NumberOfCourts, int PointsPerMatch, List<Player> Players);