using Microsoft.AspNetCore.Mvc;
using Microsoft.Extensions.Diagnostics.HealthChecks;
using WebApi.Models;


namespace WebApi.Services
{
    public interface ISensorDataService
    {
        public Task<List<SensorData>> GetSensorDataAsync();
        public Task AddSensorDataAsync(SensorData sensorData);
        
    }
}
