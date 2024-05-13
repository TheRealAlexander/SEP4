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
        public Task AddSensorData(SensorData sensorData)
        {
            if (sensorData == null)
            {
                throw new ArgumentNullException(nameof(sensorData));
            }

            return _httpClient.PostAsJsonAsync("http://indeklima_webapi:5200/AddEnvironmentData", sensorData);
        }
    }
}
