using Microsoft.AspNetCore.Mvc;
using WebApi.DAO;
using WebApi.Models;

namespace WebApi.Services
{
    public class SensorDataService : ISensorDataService

    {
        private readonly ISensorDataDAO _sensorDataDao;

        public SensorDataService(ISensorDataDAO sensorDataDao)
        {
            _sensorDataDao = sensorDataDao;
        }

        public async Task<List<SensorData>> GetSensorData()
        {
            return await _sensorDataDao.GetSensorDataAsync();
        }

        public async Task AddSensorDataAsync(SensorData sensorData)
        {
            if (sensorData == null)
            {
                throw new ArgumentNullException(nameof(sensorData));
            }
            await _sensorDataDao.AddSensorDataAsync(sensorData);
        }

        public async Task AddSensorDataGoalAsync(SensorGoal sensorGoal)
        {
            await _sensorDataDao.AddSensorDataGoalAsync(sensorGoal);
        }

        public async Task<SensorGoal> GetSensorDataGoalAsync()
        {
            return await _sensorDataDao.GetLatestSensorGoalAsync();
        }
    }
}