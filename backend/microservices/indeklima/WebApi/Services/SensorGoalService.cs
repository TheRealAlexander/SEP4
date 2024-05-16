using WebApi.DAO;
using WebApi.Models;

namespace WebApi.Services
{
    public class SensorGoalService : ISensorGoalService
    {
        private readonly ISensorGoalDAO _sensorGoalDAO;

        public SensorGoalService(ISensorGoalDAO sensorGoalDAO)
        {
            _sensorGoalDAO = sensorGoalDAO;
        }

        public async Task<SensorGoal?> GetSensorGoalAsync(int hallId)
        {
            return await _sensorGoalDAO.GetSensorGoalAsync(hallId);
        }

        public async Task AddOrUpdateSensorGoalAsync(SensorGoal sensorGoal)
        {
            await _sensorGoalDAO.AddOrUpdateSensorGoalAsync(sensorGoal);
        }

        public async Task DeleteSensorGoalAsync(int hallId)
        {
            await _sensorGoalDAO.DeleteSensorGoalAsync(hallId);
        }
    }
}