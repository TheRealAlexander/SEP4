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

    public async Task<Tournament> GetTournamentAsync(string tournamentID)
    {
        var filter = Builders<Tournament>.Filter.Eq(t => t.Id, tournamentID);
        return await _tournamentMongoCollection.Find(filter).FirstOrDefaultAsync();
    }

    public async Task<List<Player>> GetScoreboardAsync(string tournamentID)
    {
        var tournament = await GetTournamentAsync(tournamentID);
        return tournament.Players.OrderByDescending(p => p.Points).ToList();
    }

    public async Task SaveChangesAsync(Tournament updatedTournament)
    {
        var filter = Builders<Tournament>.Filter.Eq(t => t.Id, updatedTournament.Id);
        var update = Builders<Tournament>.Update
            .Set(t => t.Name, updatedTournament.Name)
            .Set(t => t.Rounds, updatedTournament.Rounds)
            .Set(t => t.Players, updatedTournament.Players)
            .Set(t => t.State, updatedTournament.State);

            await _tournamentMongoCollection.UpdateOneAsync(filter, update);
    }
    
    public async Task<List<Tournament>> GetTournamentHistoryAsync()
    {
        var filter = Builders<Tournament>.Filter.Empty;
        return await _tournamentMongoCollection.Find(filter).ToListAsync();
    }
}