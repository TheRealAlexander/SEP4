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
        public async Task<List<SensorData>> GetSensorData(int limit)
        {
            return await _httpClient.GetFromJsonAsync<List<SensorData>>($"http://indeklima_webapi:5200/GetEnvironmentData/{limit}");
        }

        public async Task<SensorData> GetSensorData(DateTime dateTime1, DateTime dateTime2)
        {
            return await _httpClient.GetFromJsonAsync<SensorData>($"http://indeklima_webapi:5200/GetEnvironmentData/{dateTime1}/{dateTime2}");
        }

        public async Task SetPrefClimateValues(int temp, int humidity)
        {
            await _httpClient.PostAsJsonAsync($"http://indeklima_webapi:5200/SetPrefClimateValues/{temp}/{humidity}");
        }
    }
}
