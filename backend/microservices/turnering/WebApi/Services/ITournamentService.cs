using WebApi.Models;

namespace WebApi.Services;

public interface ITournamentService
{
    Task AddTournamentAsync(TournamentCreationDTO tournamentDTO);
}