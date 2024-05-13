using Microsoft.AspNetCore.Mvc;
using Microsoft.Extensions.Diagnostics.HealthChecks;
using SharedObjects.Models;


namespace Broker.Services
{
    public interface IBrokerService
    {
        public Task<List<SensorData>> GetSensorData(int limit);
        public Task<SensorData> GetSensorData(DateTime dateTime1, DateTime dateTime2);
        public Task SetPrefClimateValues(int temp, int humidity);

    }
}
