using Microsoft.AspNetCore.Mvc;
using Microsoft.Extensions.Diagnostics.HealthChecks;
using SharedObjects.Models;
using System.Collections.Generic;


namespace Broker.Services
{
    public interface IBrokerService
    {
        public Task<List<SensorData>?> GetSensorData(int hallId);

        // Corresponds to GetAllTournaments
        public Task<ActionResult<List<Tournament>>> GetTournaments();

        // Corresponds to CreateTournament
        public Task<ActionResult<Tournament>> CreateTournament(Tournament tournamentData);

        // Corresponds to UpdateTournament
        public Task<ActionResult<Tournament>> UpdateTournament(string tournamentID, Tournament tournamentData);

        // Corresponds to RemoveTournament
        public Task<ActionResult> DeleteTournament(string tournamentID);

        // Corresponds to AddParticipant
        public Task<ActionResult<string>> AddParticipant(string tournamentID, string participant);

        // Corresponds to RemoveParticipant
        public Task<ActionResult> RemoveParticipant(string tournamentID, string participant);

        public Task<string> Login(string user);

        public Task<string> FetchSuperUsers();

        public Task<string> FetchNonAdminUsers();

        public Task<string> AdjustUserPermissions(string usersToChange);

        public Task<string> RegisterUser(string user);
    }
}
