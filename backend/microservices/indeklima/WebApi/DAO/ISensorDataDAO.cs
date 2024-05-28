using WebApi.Models;

namespace WebApi.DAO
{
    public interface ISensorDataDAO
    {
        Task<List<SensorData>> GetSensorDataAsync(int hallId);
        Task<List<SensorData>> GetSensorDataAsync(int hallId, int limit);
        Task<List<SensorData>> GetSensorDataAsync(int hallId, DateTime startDate, DateTime endDate);
        Task AddSensorDataAsync(SensorData sensorData);
    }
}