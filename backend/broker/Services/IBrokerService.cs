using Microsoft.AspNetCore.Mvc;
using Microsoft.Extensions.Diagnostics.HealthChecks;
using SharedObjects.Models;


namespace Broker.Services
{
    public interface IBrokerService
    {
        public Task<List<SensorData>> GetSensorData();

        // Corresponds to GetAllTournaments
        public Task<ActionResult<List<Tournament>>> GetTournaments();

        // Corresponds to CreateTournament
        public Task<ActionResult<Tournament>> CreateTournament(Tournament tournamentData);

        // Corresponds to UpdateTournament
        public Task<ActionResult<Tournament>> UpdateTournament(int tournamentID, Tournament tournamentData);

        // Corresponds to RemoveTournament
        public Task<ActionResult> DeleteTournament(int tournamentID);

        // Corresponds to AddParticipant
        public Task<ActionResult<Participant>> AddParticipant(int tournamentID, string participant);

        // Corresponds to RemoveParticipant
        public Task<ActionResult> RemoveParticipant(int tournamentID, string participant);
    }
}
