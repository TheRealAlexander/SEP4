using Microsoft.AspNetCore.Mvc;
using SharedObjects.Models;

namespace Broker.Services
{
    public class BrokerService : IBrokerService

    {

        private readonly HttpClient _httpClient;

        public BrokerService(HttpClient httpClient)
        {
            _httpClient = httpClient;
        }
        public async Task<List<SensorData>> GetSensorData()
        {
            return await _httpClient.GetFromJsonAsync<List<SensorData>>("http://indeklima_webapi:5200/GetEnvironmentData");
        }

        public async Task<ActionResult<List<Tournament>>> GetTournaments()
        {
            return await _httpClient.GetFromJsonAsync<ActionResult<List<Tournament>>>("http://turnering_webapi:5100/tournaments");
        }

        public async Task<ActionResult<Tournament>> CreateTournament(Tournament tournamentData)
        {
            return await _httpClient.PostAsJsonAsync<ActionResult<Tournament>>("http://turnering_webapi:5100/tournaments", tournamentData);
        }

        public async Task<ActionResult<Tournament>> UpdateTournament(string tournamentID, Tournament tournamentData)
        {
            return await _httpClient.PutAsJsonAsync<ActionResult<Tournament>>($"http://turnering_webapi:5100/tournaments/{tournamentID}", tournamentData);
        }

        public async Task<ActionResult> DeleteTournament(string tournamentID)
        {
            return await _httpClient.DeleteAsync($"http://turnering_webapi:5100/tournaments/{tournamentID}");
        }

        public async Task<ActionResult<Participant>> AddParticipant(string tournamentID, string participant)
        {
            return await _httpClient.PostAsJsonAsync<ActionResult<Participant>>($"http://turnering_webapi:5100/tournaments/{tournamentID}/participants", participant);
        }

        public async Task<ActionResult> RemoveParticipant(string tournamentID, string participant)
        {
            return await _httpClient.DeleteAsync($"http://turnering_webapi:5100/tournaments/{tournamentID}/participants/{participant}");
        }


    }
}
