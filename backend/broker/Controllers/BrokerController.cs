using Microsoft.AspNetCore.Mvc;
using SharedObjects.Models;
using Broker.Services;
using System.Collections.Generic;
using System.Threading.Tasks;

namespace Broker.Controllers
{
    [ApiController]
    [Route("[controller]")]
    public class BrokerController : ControllerBase
    {
        private IBrokerService _brokerService;

        public BrokerController(IBrokerService brokerService)
        {
            _brokerService = brokerService;
        }

        [HttpGet("GetSensorData")]
        public async Task<List<SensorData>> GetSensorData()
        {
            return await _brokerService.GetSensorData();
        }

        // Corresponds to GetAllTournaments
        [HttpGet("tournaments")]
        public async Task<ActionResult<List<Tournament>>> GetTournaments()
        {
            // Implementation here
        }

        // Corresponds to CreateTournament
        [HttpPost("tournaments")]
        public async Task<ActionResult<Tournament>> CreateTournament(Tournament tournamentData)
        {
            // Implementation here
        }

        // Corresponds to UpdateTournament
        [HttpPut("tournaments/{tournamentID}")]
        public async Task<ActionResult<Tournament>> UpdateTournament(int tournamentID, Tournament tournamentData)
        {
            // Implementation here
        }

        // Corresponds to RemoveTournament
        [HttpDelete("tournaments/{tournamentID}")]
        public async Task<ActionResult> DeleteTournament(int tournamentID)
        {
            // Implementation here
        }

        // Corresponds to AddParticipant
        [HttpPost("tournaments/{tournamentID}/participants")]
        public async Task<ActionResult<Participant>> AddParticipant(int tournamentID, string participant)
        {
            // Implementation here
        }

        // Corresponds to RemoveParticipant
        [HttpDelete("tournaments/{tournamentID}/participants/{participant}")]
        public async Task<ActionResult> RemoveParticipant(int tournamentID, string participant)
        {
            // Implementation here
        }
    }
}