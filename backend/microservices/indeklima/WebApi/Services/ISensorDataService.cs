using Microsoft.AspNetCore.Mvc;
using Microsoft.Extensions.Diagnostics.HealthChecks;
using WebApi.Models;


namespace WebApi.Services
{
    public interface ISensorDataService
    {
        public Task<List<SensorData>> GetSensorData(int hallId);
        public Task<List<SensorData>> GetSensorData(int hallId, int limit);

        public Task<List<SensorData>> GetSensorData(int hallId, DateTime startDate, DateTime endDate);
        public Task AddSensorData(SensorData sensorData);
    }
}
