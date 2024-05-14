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
        public async Task<List<SensorData>> GetSensorData(int hallId)
        {
            if (hallId == null)
            {
                throw new ArgumentNullException(nameof(hallId));
            }
            return await _sensorDataDao.GetSensorDataAsync(hallId);
        }
        public Task AddSensorData(SensorData sensorData)
        {
            if (sensorData == null)
            {
                throw new ArgumentNullException(nameof(sensorData));
            }

            return _sensorDataDao.AddSensorDataAsync(sensorData);
        }
        public async Task<List<SensorData>> GetSensorData(int hallId, int limit)
        {
            return await _sensorDataDao.GetSensorDataAsync(hallId, limit);
        }
        public async Task<List<SensorData>> GetSensorData(int hallId, DateTime startDate, DateTime endDate)
        {
            if (hallId == null)
            {
                throw new ArgumentNullException(nameof(hallId));
            }
            if (startDate == null || endDate == null)
            {
                throw new ArgumentNullException(nameof(startDate));
            }

            return await _sensorDataDao.GetSensorDataAsync(hallId, startDate, endDate);
        }
    }
}
