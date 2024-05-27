namespace WebApi.Models;

public record TournamentCreationDTO(string Name, string Format, int NumberOfCourts, int PointsPerMatch, DateTime StartTime, string Description, List<string> Players);