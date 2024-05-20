using MongoDB.Bson;
using MongoDB.Driver;
using turnering.Models.Tournament;
using WebApi.Models;

namespace WebApi.DAO;

public class TournamentDAO : ITournamentDAO
{
    private readonly IMongoCollection<TournamentWithFormatAsStringDto> _tournamentMongoCollection;
    
    public TournamentDAO(MongoDbContext context)
    {
        _tournamentMongoCollection = context.Database.GetCollection<TournamentWithFormatAsStringDto>("Tournament");
    }


    public async Task AddTournamentAsync(Tournament tournament)
    {
        //Convert to serializable object
        TournamentWithFormatAsStringDto tournamentSaveDB = new TournamentWithFormatAsStringDto(tournament.Name, tournament.Format.TournamentFormat, tournament.NumberOfPlayers, tournament.NumberOfCourts, tournament.PointsPerMatch, tournament.Players);
        await _tournamentMongoCollection.InsertOneAsync(tournamentSaveDB);
    }

    public async Task<Tournament> GetTournamentAsync(string tournamentID)
    {
        var filter = Builders<TournamentWithFormatAsStringDto>.Filter.Eq(t => t.Id, tournamentID);
        TournamentWithFormatAsStringDto tournaments = await _tournamentMongoCollection.Find(filter).FirstOrDefaultAsync();
        //Converts to Tournament object
        Tournament tournament = new Tournament(tournaments.Name, GetTournamentFormat(tournaments.Format), tournaments.NumberOfPlayers, tournaments.NumberOfCourts, tournaments.PointsPerMatch, tournaments.Players);

        return tournament;
    }

    public async Task<List<Player>> GetScoreboardAsync(string tournamentID)
    {
        var tournament = await GetTournamentAsync(tournamentID);
        return tournament.Players.OrderBy(p => p.Points).ToList();
    }

    public async Task<List<TournamentWithFormatAsStringDto>> GetTournamentHistoryAsync()
    {
        var filter = Builders<TournamentWithFormatAsStringDto>.Filter.Empty;
        List<TournamentWithFormatAsStringDto> tournaments = await _tournamentMongoCollection.Find(filter).ToListAsync();
        return tournaments.ToList();
    }

    private TournamentFormat GetTournamentFormat(string format)
    {
        switch (format)
        {
            case "Mexicano":
                return new Mexicano();
            case "Americano":
                return new Americano();
            default:
                throw new ArgumentException("Invalid tournament type");
        }
    }
}