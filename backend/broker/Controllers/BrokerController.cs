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
        public async Task<ActionResult<List<SensorData>>> GetSensorData(int hallId)
        {
            var result = await _brokerService.GetSensorData(hallId);
            if (result == null)
            {
                return NoContent();
            }
            return Ok(result);
        }



        [HttpGet("tournaments")]
        public async Task<IActionResult> GetTournaments()
        {
            var result = await _brokerService.GetTournaments();
            if (result?.Value == null)
            {
                return NoContent();
            }
            return Ok(result.Value);
        }

        // Corresponds to CreateTournament
        [HttpPost("tournaments")]
        public async Task<ActionResult<Tournament>> CreateTournament(Tournament tournamentData)
        {
            return await _brokerService.CreateTournament(tournamentData);
        }

        // Corresponds to UpdateTournament
        [HttpPut("tournaments/{tournamentID}")]
        public async Task<ActionResult<Tournament>> UpdateTournament(string tournamentID, Tournament tournamentData)
        {
            return await _brokerService.UpdateTournament(tournamentID, tournamentData);
        }

        // Corresponds to RemoveTournament
        [HttpDelete("tournaments/{tournamentID}")]
        public async Task<ActionResult> DeleteTournament(string tournamentID)
        {
            return await _brokerService.DeleteTournament(tournamentID);
        }

        // Corresponds to AddParticipant
        [HttpPost("tournaments/{tournamentID}/participants")]
        public async Task<ActionResult<string>> AddParticipant(string tournamentID, string participant)
        {
            return await _brokerService.AddParticipant(tournamentID, participant);
        }

        // Corresponds to RemoveParticipant
        [HttpDelete("tournaments/{tournamentID}/participants/{participant}")]
        public async Task<ActionResult> RemoveParticipant(string tournamentID, string participant)
        {
            return await _brokerService.RemoveParticipant(tournamentID, participant);
        }

        [HttpPost("auth/login")]
        public async Task<IActionResult> Login([FromBody] string user)
        {
            var result = await _brokerService.Login(user);
            return Content(result, "application/json");
        }

        [HttpGet("superUsers")]
        public async Task<IActionResult> FetchSuperUsers()
        {
            var result = await _brokerService.FetchSuperUsers();
            return Content(result, "application/json");
        }

        [HttpGet("nonSuperUsers")]
        public async Task<IActionResult> FetchNonAdminUsers()
        {
            var result = await _brokerService.FetchNonAdminUsers();
            return Content(result, "application/json");
        }

        [HttpPut("adjustUserPermissions/{usersToChange}")]
        public async Task<IActionResult> AdjustUserPermissions(string usersToChange)
        {
            var result = await _brokerService.AdjustUserPermissions(usersToChange);
            return Content(result, "application/json");
        }

        [HttpGet("auth/register")]
        public async Task<IActionResult> RegisterUser([FromBody] string user)
        {
            var result = await _brokerService.RegisterUser(user);
            return Content(result, "application/json");
        }
    }
}