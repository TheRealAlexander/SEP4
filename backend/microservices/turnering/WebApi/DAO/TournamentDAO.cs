using MongoDB.Bson;
using MongoDB.Driver;
using WebApi.Models;

namespace WebApi.DAO;

public class TournamentDAO : ITournamentDAO
{
    private readonly IMongoCollection<Tournament> _tournamentMongoCollection;
    
    public TournamentDAO(MongoDbContext context)
    {
        _tournamentMongoCollection = context.Database.GetCollection<Tournament>("Tournament");
    }


    public async Task AddTournamentAsync(Tournament tournament)
    {
        await _tournamentMongoCollection.InsertOneAsync(tournament);
    }

    public async Task<Tournament> GetTournamentAsync(int tournamentID)
    {
        var filter = Builders<Tournament>.Filter.Eq(t => t.Id, tournamentID.ToString());
        return await _tournamentMongoCollection.Find(filter).FirstOrDefaultAsync();
    }

    public async Task<List<Player>> GetScoreboardAsync(int tournamentID)
    {
        var tournament = await GetTournamentAsync(tournamentID);
        return tournament.Players.OrderBy(p => p.Points).ToList();
    }

    public async Task<List<Tournament>> GetTournamentHistoryAsync()
    {
        var filter = Builders<Tournament>.Filter.Empty;
        return await _tournamentMongoCollection.Find(filter).ToListAsync();
    }
}