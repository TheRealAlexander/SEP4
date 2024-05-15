namespace WebApi.Models;

public record TournamentCreationDTO(string Name, string TournamentFormat, int NumberOfCourts, List<Player> Players);