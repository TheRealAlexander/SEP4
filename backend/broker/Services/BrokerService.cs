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
            return await _httpClient.GetFromJsonAsync<List<SensorData>>("https://localhost:5001/GetEnvironmentData");
        }
        public Task AddSensorData(SensorData sensorData)
        {
            if (sensorData == null)
            {
                throw new ArgumentNullException(nameof(sensorData));
            }

            return _httpClient.PostAsJsonAsync("https://localhost:5001/AddEnvironmentData", sensorData);
        }
    }
}
