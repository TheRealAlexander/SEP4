using Microsoft.AspNetCore.Mvc;
using WebApi.DAO;
using WebApi.Models;

namespace WebApi.Services
{
    public class SensorDataService : ISensorDataService

    {
        private readonly ISensorDataDAO _sensorDataDao;

        public SensorDataService(SensorDataDao sensorDataDao)
        {
            _sensorDataDao = sensorDataDao;
        }
        public async Task<List<SensorData>> GetSensorData()
        {
            return await _sensorDataDao.GetSensorDataAsync();
        }
        public void AddSensorData(SensorData sensorData)
        {
            if (sensorData == null)
            {
                throw new ArgumentNullException(nameof(sensorData));
            }

            _sensorDataDao.AddSensorDataAsync(sensorData);
        }
    }
}
