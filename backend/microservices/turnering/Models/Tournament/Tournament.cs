using MongoDB.Bson;
using MongoDB.Bson.Serialization.Attributes;

namespace WebApi.Models;

public class Tournament
{
    [BsonId]
    [BsonRepresentation(MongoDB.Bson.BsonType.ObjectId)]
    public string Id { get; set; } = ObjectId.GenerateNewId().ToString();
    public string Name { get; set; }
    public TournamentFormat Format { get; set; }
    public int NumberOfPlayers { get; set; }
    public int NumberOfCourts { get; set; }
    public List<Player> Players { get; set; }

    public Tournament(string name, TournamentFormat format, int numberOfPlayers, int numberOfCourts, List<Player> players)
    {
        Name = name;
        Format = format;
        NumberOfPlayers = numberOfPlayers;
        NumberOfCourts = numberOfCourts;
        Players = players;
    }
}