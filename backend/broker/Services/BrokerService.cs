using Microsoft.AspNetCore.Mvc;
using SharedObjects.Models;
using System.Collections.Generic;
using System.Net.Http;
using System.Net.Http.Json;
using System.Threading.Tasks;
using Newtonsoft.Json;

namespace Broker.Services
{
    public class BrokerService : IBrokerService
    {
        private readonly HttpClient _httpClient;

        public BrokerService(HttpClient httpClient)
        {
            _httpClient = httpClient;
        }

        public async Task<List<SensorData>?> GetSensorData()
        {
            try
            {
                return await _httpClient.GetFromJsonAsync<List<SensorData>>("http://indeklima_webapi:5200/GetEnvironmentData");
            }
            catch (HttpRequestException ex)
            {
                // Handle exception
                throw new Exception("Error getting sensor data", ex);
            }
        }

        public async Task<ActionResult<List<Tournament>>> GetTournaments()
        {
            var response = await _httpClient.GetAsync("http://turnering_webapi:5101/tournaments");
            if (response.IsSuccessStatusCode)
            {
                var jsonString = await response.Content.ReadAsStringAsync();
                var tournaments = JsonConvert.DeserializeObject<List<Tournament>>(jsonString);
                return new ActionResult<List<Tournament>>(tournaments);
            }
            else
            {
                return new NotFoundResult();
            }
        }

        public async Task<ActionResult<Tournament>> CreateTournament(Tournament tournamentData)
        {
            try
            {
                var response = await _httpClient.PostAsJsonAsync<Tournament>("http://turnering_webapi:5101/tournaments", tournamentData);
                if (response.IsSuccessStatusCode)
                {
                    var jsonString = await response.Content.ReadAsStringAsync();
                    var tournament = JsonConvert.DeserializeObject<Tournament>(jsonString);
                    return new ActionResult<Tournament>(tournament);
                }
                else
                {
                    return new NotFoundResult();
                }
            }
            catch (HttpRequestException ex)
            {
                // Handle exception
                throw new Exception("Error creating tournament", ex);
            }
        }

        public async Task<ActionResult<Tournament>> UpdateTournament(string tournamentID, Tournament tournamentData)
        {
            try
            {
                var response = await _httpClient.PutAsJsonAsync<Tournament>($"http://turnering_webapi:5101/tournaments/{tournamentID}", tournamentData);
                if (response.IsSuccessStatusCode)
                {
                    var jsonString = await response.Content.ReadAsStringAsync();
                    var tournament = JsonConvert.DeserializeObject<Tournament>(jsonString);
                    return new ActionResult<Tournament>(tournament);
                }
                else
                {
                    return new NotFoundResult();
                }
            }
            catch (HttpRequestException ex)
            {
                // Handle exception
                throw new Exception("Error updating tournament", ex);
            }
        }

        public async Task<ActionResult> DeleteTournament(string tournamentID)
        {
            var response = await _httpClient.DeleteAsync($"http://turnering_webapi:5101/tournaments/{tournamentID}");
            return response.IsSuccessStatusCode ? new OkResult() : null as ActionResult;
        }

        public async Task<ActionResult<string>> AddParticipant(string tournamentID, string participant)
        {
            var response = await _httpClient.PostAsJsonAsync<string>($"http://turnering_webapi:5101/tournaments/{tournamentID}/participants", participant);
            if (response.IsSuccessStatusCode)
            {
                var result = await response.Content.ReadAsStringAsync();
                return result;
            }
            else
            {
                return null;
            }
        }

        public async Task<ActionResult> RemoveParticipant(string tournamentID, string participant)
        {
            var response = await _httpClient.DeleteAsync($"http://turnering_webapi:5101/tournaments/{tournamentID}/participants/{participant}");
            return response.IsSuccessStatusCode ? new OkResult() : null as ActionResult;
        }
    }
}