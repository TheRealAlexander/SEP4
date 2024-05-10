using WebApi.Models;

namespace WebApi.DAO
{
    public interface ISensorDataDAO
    {
        Task<List<SensorData>> GetSensorDataAsync();
        Task AddSensorDataAsync(SensorData sensorData);
        Task AddSensorDataGoalAsync(SensorGoal sensorGoal);
        Task <SensorGoal> GetLatestSensorGoalAsync();
    }
}