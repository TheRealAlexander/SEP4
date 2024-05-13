using Microsoft.AspNetCore.Mvc;
using Microsoft.Extensions.Diagnostics.HealthChecks;
using SharedObjects.Models;


namespace Broker.Services
{
    public interface IBrokerService
    {
        public Task<List<SensorData>> GetSensorData();
        public Task AddSensorData(SensorData sensorData);
    }
}
