using WebApi.Models;

namespace WebApi.DAO;

public interface ISensorGoalDAO
{
    Task<SensorGoal?> GetSensorGoalAsync(int hallId);
    Task AddOrUpdateSensorGoalAsync(SensorGoal sensorGoal);
    Task DeleteSensorGoalAsync(int hallId);
}