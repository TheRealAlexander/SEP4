using Microsoft.AspNetCore.Mvc;
using Microsoft.Extensions.Diagnostics.HealthChecks;
using WebApi.Models;


namespace WebApi.Services
{
    public interface ISensorDataService
    {
        public Task<List<SensorData>> GetSensorData();
        public Task AddSensorData(SensorData sensorData);
    }
}
