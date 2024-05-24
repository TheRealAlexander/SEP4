using MongoDB.Bson;
using MongoDB.Bson.Serialization.Attributes;

namespace WebApi.Models;

public class Tournament
{
    [BsonId]
    [BsonRepresentation(MongoDB.Bson.BsonType.ObjectId)]
    public string Id { get; set; } = ObjectId.GenerateNewId().ToString();
    public string Name { get; set; }
    public string Format { get; set; }
    public int NumberOfCourts { get; set; }
    public int PointsPerMatch { get; set; }
    public DateTime StartTime { get; set; }
    public string Description { get; set; }
    public List<Player> Players { get; set; }
    public int State { get; set; } = 1;
    public List<Round> Rounds { get; set; } = new List<Round>();
    public int NextRoundNumber { get; set; } = 1;
    private List<Player> SkippedARound { get; set; } = new List<Player>();
    private List<Player> SkippedLastRound { get; set; } = new List<Player>();

    public Tournament(string name, string format, int numberOfCourts, int pointsPerMatch, DateTime startTime, string description, List<Player> players)
    {
        Name = name;
        Format = format;
        NumberOfCourts = numberOfCourts;
        PointsPerMatch = pointsPerMatch;
        StartTime = startTime;
        Description = description;
        Players = players;
    }

    public Round GenerateRound(List<Player> players)
    {
        switch (Format)
        {
            case "Americano" : return Americano.GenerateRound(players, this);
            case "Mexicano" : return Mexicano.GenerateRound(players, this);
        }

        throw new ArgumentException("Invalid tournament format");
    }
    
    public List<Player> ShufflePlayers()
    {
        Random rng = new Random();
        int n = Players.Count;
        while (n > 1)
        {
            n--;
            int k = rng.Next(n + 1);
            (Players[k], Players[n]) = (Players[n], Players[k]);
        }
        return Players;
    }
    
    public List<Player> SkipPlayers()
    {
        int i = 0;
        List<Player> playingThisRound = new List<Player>(Players);
        List<Player> skippingThisRound = new List<Player>();
        while (playingThisRound.Count > NumberOfCourts * 4)
        {
            if (!SkippedARound.Contains(playingThisRound[i]) && (Players.Count >= NumberOfCourts * 8 || !SkippedLastRound.Contains(playingThisRound[i])))
            {
                SkippedARound.Add(playingThisRound[i]);
                skippingThisRound.Add(playingThisRound[i]);
                playingThisRound.RemoveAt(i);
                i--;
            }

            i++;

            if (SkippedARound.Count == Players.Count)
            {
                SkippedARound.Clear();
                i = 0;
            }
        }
        SkippedLastRound = skippingThisRound;
        return playingThisRound;
    }
}