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
    public List<Round> Rounds { get; set; }
    public int NextRoundNumber { get; set; } = 1;
    private List<Player>? SkippedARound { get; set; }
    private List<Player>? SkippedLastRound { get; set; }

    public Tournament(string name, string format, int numberOfCourts, int pointsPerMatch, DateTime startTime, string description, List<Player> players)
    {
        Name = name;
        Format = format;
        NumberOfCourts = numberOfCourts;
        PointsPerMatch = pointsPerMatch;
        StartTime = startTime;
        Description = description;
        Players = players;
        Rounds = new List<Round>();
        SkippedARound = new List<Player>();
        SkippedLastRound = new List<Player>();
    }

    public Round GenerateRound(List<Player> players)
    {
        Round round;
        switch (Format)
        {
            case "Americano" : round = Americano.GenerateRound(players, this);
                break;
            case "Mexicano" : round = Mexicano.GenerateRound(players, this);
                break;
            default : throw new ArgumentException("Invalid tournament format");
        }
        
        return round;
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
        if (SkippedARound == null || SkippedLastRound == null)
        {
            Console.WriteLine("Initialization error: Skipped lists are null.");
            SkippedARound = new List<Player>();  // Re-initializing if found null, though ideally this shouldn't happen.
            SkippedLastRound = new List<Player>();
        }
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