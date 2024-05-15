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
            return await _brokerService.GetTournaments();
        }

        // Corresponds to CreateTournament
        [HttpPost("tournaments")]
        public async Task<ActionResult<Tournament>> CreateTournament(Tournament tournamentData)
        {
            return await _brokerService.CreateTournament(tournamentData);
        }

        // Corresponds to UpdateTournament
        [HttpPut("tournaments/{tournamentID}")]
        public async Task<ActionResult<Tournament>> UpdateTournament(int tournamentID, Tournament tournamentData)
        {
            return await _brokerService.UpdateTournament(tournamentID, tournamentData);
        }

        // Corresponds to RemoveTournament
        [HttpDelete("tournaments/{tournamentID}")]
        public async Task<ActionResult> DeleteTournament(int tournamentID)
        {
            return await _brokerService.DeleteTournament(tournamentID);
        }

        // Corresponds to AddParticipant
        [HttpPost("tournaments/{tournamentID}/participants")]
        public async Task<ActionResult<Participant>> AddParticipant(int tournamentID, string participant)
        {
            return await _brokerService.AddParticipant(tournamentID, participant);
        }

        // Corresponds to RemoveParticipant
        [HttpDelete("tournaments/{tournamentID}/participants/{participant}")]
        public async Task<ActionResult> RemoveParticipant(int tournamentID, string participant)
        {
            return await _brokerService.RemoveParticipant(tournamentID, participant);
        }
    }
}