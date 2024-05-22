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
            try
            {
                return await _sensorGoalDAO.GetSensorGoalAsync(hallId);
            }
            catch (Exception ex)
            {
                throw new Exception($"Error retrieving sensor goal: {ex.Message}");
            }
        }

        public async Task AddOrUpdateSensorGoalAsync(SensorGoal sensorGoal)
        {
            try
            {
                await _sensorGoalDAO.AddOrUpdateSensorGoalAsync(sensorGoal);
            }
            catch (Exception ex)
            {
                throw new Exception($"Error adding or updating sensor goal: {ex.Message}");
            }
        }

        public async Task DeleteSensorGoalAsync(int hallId)
        {
            try
            {
                await _sensorGoalDAO.DeleteSensorGoalAsync(hallId);
            }
            catch (Exception ex)
            {
                throw new Exception($"Error deleting sensor goal: {ex.Message}");
            }
        }
    }
}