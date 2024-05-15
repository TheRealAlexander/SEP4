using WebApi.Models;

namespace WebApi.Services;

public interface IQueueService
{
    Task EnqueueSensorGoalAsync(SensorGoal sensorGoal);
    Task<SensorGoal?> DequeueSensorGoalAsync();
}