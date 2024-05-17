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
    public int PointsPerMatch { get; set; }
    public List<Player> Players { get; set; }
    public bool FirstRound { get; set; } = true;
    public List<Player> SkippedARound { get; set; } = new List<Player>();
    public List<Player> SkippedLastRound { get; set; } = new List<Player>();

    public Tournament(string name, TournamentFormat format, int numberOfPlayers, int numberOfCourts, int pointsPerMatch, List<Player> players, List<Player> skippedARound)
    {
        Name = name;
        Format = format;
        NumberOfPlayers = numberOfPlayers;
        NumberOfCourts = numberOfCourts;
        PointsPerMatch = pointsPerMatch;
        Players = players;
        SkippedARound = skippedARound;
    }
    
    public List<Player> ShufflePlayers()
    {
        Random rng = new Random();
        int n = Players.Count;
        while (n > 1)
        {
            n--;
            int k = rng.Next(n + 1);
            Player value = Players[k];
            Players[k] = Players[n];
            Players[n] = value;
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
            if (i >= playingThisRound.Count)
            {
                break;
            }
        
            if (!SkippedARound.Contains(playingThisRound[i]) && !SkippedLastRound.Contains(playingThisRound[i]))
            {
                SkippedARound.Add(playingThisRound[i]);
                skippingThisRound.Add(playingThisRound[i]);
                i++;
            }
            else
            {
                Player skippedPlayer = playingThisRound[i];
                playingThisRound.RemoveAt(i);
                playingThisRound.Add(skippedPlayer);
            }
            
            if (i >= playingThisRound.Count)
            {
                SkippedARound.Clear();
                i = 0;
            }
        }
        SkippedLastRound = skippingThisRound;
        return playingThisRound;
    }

}