using Microsoft.AspNetCore.Mvc;
using WebApi.Services;
using WebApi.Models; // Replace with your actual namespace

namespace Broker.Controllers
{
    [ApiController]
    [Route("[controller]")]
    public class BrokerController : ControllerBase
    {
        private readonly ISensorDataService _sensorDataService;

        public BrokerController(ISensorDataService sensorDataService)
        {
            _sensorDataService = sensorDataService;
        }

        [HttpGet]
        public async Task<List<SensorData>> GetSensorData()
        {
            return await _sensorDataService.GetSensorData();
        }
    }
}