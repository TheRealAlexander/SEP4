namespace WebApi.Models;

public record TournamentCreationDTO(string Name, string TournamentFormat, int NumberOfCourts, int PointsPerMatch, DateTime StartTime, string Description, List<string> Players);