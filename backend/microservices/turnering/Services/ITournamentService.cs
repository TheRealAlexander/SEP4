using WebApi.Models;

namespace WebApi.Services;

public interface ITournamentService
{
    Task AddTournament(Tournament tournament);
}