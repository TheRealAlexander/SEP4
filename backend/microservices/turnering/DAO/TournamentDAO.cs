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
}