using MongoDB.Bson;
using MongoDB.Bson.Serialization.Attributes;
using WebApi.Models;

namespace turnering.Models.Tournament
{
    public class TournamentWithFormatAsStringDto
    {
    [BsonId]
    [BsonRepresentation(MongoDB.Bson.BsonType.ObjectId)]
    public string Id { get; set; } = ObjectId.GenerateNewId().ToString();
    public string Name { get; set; }
    public string Format { get; set; }
    public int NumberOfPlayers { get; set; }
    public int NumberOfCourts { get; set; }
    public int PointsPerMatch { get; set; }
    public List<Player> Players { get; set; }
    public int NextRoundNumber { get; set; } = 1;
    public List<Player> SkippedARound { get; set; } = new List<Player>();
    public List<Player> SkippedLastRound { get; set; } = new List<Player>();

    public TournamentWithFormatAsStringDto(string name, string format, int numberOfPlayers, int numberOfCourts, int pointsPerMatch, List<Player> players)
    {
        Name = name;
        Format = format;
        NumberOfPlayers = numberOfPlayers;
        NumberOfCourts = numberOfCourts;
        PointsPerMatch = pointsPerMatch;
        Players = players;
    }
    
    }
}