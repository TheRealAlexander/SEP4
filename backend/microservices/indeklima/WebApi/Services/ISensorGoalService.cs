using WebApi.Models;

namespace WebApi.Services
{
    public interface ISensorGoalService
    {
        Task<SensorGoal?> GetSensorGoalAsync(int hallId);
        Task AddOrUpdateSensorGoalAsync(SensorGoal sensorGoal);
        Task DeleteSensorGoalAsync(int hallId);
    }
}