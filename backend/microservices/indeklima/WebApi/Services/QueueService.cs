using System.Collections.Concurrent;
using System.Threading.Tasks;
using Microsoft.Extensions.Logging;
using Newtonsoft.Json;
using WebApi.Models;

namespace WebApi.Services
{
    public class QueueService : IQueueService
    {
        private readonly ConcurrentQueue<SensorGoal> _queue = new ConcurrentQueue<SensorGoal>();
        private readonly ILogger<QueueService> _logger;

        public QueueService(ILogger<QueueService> logger)
        {
            _logger = logger;
            _logger.LogInformation("QueueService instance created. Initial Queue count: {QueueCount}", _queue.Count);
        }

        public Task EnqueueSensorGoalAsync(SensorGoal sensorGoal)
        {
            _queue.Enqueue(sensorGoal);
            _logger.LogInformation("Sensor goal enqueued: {@SensorGoal}. Queue count: {@QueueCount}", JsonConvert.SerializeObject(sensorGoal), _queue.Count);
            return Task.CompletedTask;
        }

        public Task<SensorGoal?> DequeueSensorGoalAsync()
        {
            if (_queue.TryDequeue(out var sensorGoal))
            {
                _logger.LogInformation("Sensor goal dequeued: {@SensorGoal}. Queue count: {@QueueCount}", JsonConvert.SerializeObject(sensorGoal), _queue.Count);
                return Task.FromResult<SensorGoal?>(sensorGoal);
            }
            else
            {
                _logger.LogWarning("Sensor goal dequeue attempted, but queue was empty.");
                return Task.FromResult<SensorGoal?>(null);
            }
        }
    }
}