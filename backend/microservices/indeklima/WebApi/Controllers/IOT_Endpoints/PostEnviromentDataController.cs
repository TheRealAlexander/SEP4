using Microsoft.AspNetCore.Mvc;
using WebApi.Models;
using WebApi.Models.Dto;
using WebApi.Services;

namespace WebApi.Controllers
{
    [ApiController]
    [Route("[controller]")]
    public class PostEnviromentDataController : ControllerBase
    {
        private ISensorDataService _sensorDataService;

        public PostEnviromentDataController(ISensorDataService sensorDataService)
        {
            _sensorDataService = sensorDataService;
        }

        [HttpPost]
        [Authorize(Policy = "MustBeAdmin")]
        public IActionResult PostSensorData(IOTSensorDataDto data)
        {
            try
            {
                SensorData sensorData = new SensorData
                {
                    Temperature = data.Temperature,
                    Humidity = data.Humidity,
                    Timestamp = DateTime.Now
                };

                _sensorDataService.AddSensorData(sensorData);
                SensorGoal newSensorGoal = _sensorDataService.GetSensorDataGoal();
                
                if (newSensorGoal != null)
                {
                    return Ok(newSensorGoal);
                }
                
                return Ok(0);
            }
            catch (Exception e)
            {
                return BadRequest(new { success = false, error = e.Message });
            }
        }
        }
    }
}