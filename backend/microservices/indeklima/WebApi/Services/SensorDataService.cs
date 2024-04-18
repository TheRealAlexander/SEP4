using Microsoft.AspNetCore.Mvc;
using WebApi.DAO;

namespace WebApi.Services
{
    public class SensorDataService : ISensorDataService

    {
        private readonly SensorDataDao _sensorDataDao;

        public SensorDataService(SensorDataDao sensorDataDao)
        {
            _sensorDataDao = sensorDataDao;
        }
        public IActionResult GetSensorData()
        {
            return new OkObjectResult(_sensorDataDao.GetSensorDataAsync());
        }
    }
}
