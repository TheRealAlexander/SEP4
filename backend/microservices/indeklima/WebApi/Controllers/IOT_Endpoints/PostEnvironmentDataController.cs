using System.Threading.Tasks;
using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Mvc;
using Newtonsoft.Json;
using WebApi.Models;
using WebApi.Models.Dto;
using WebApi.Services;

namespace WebApi.Controllers
{
    [ApiController]
    [Route("[controller]")]
    public class PostEnvironmentDataController : ControllerBase
    {
        private readonly ISensorDataService _sensorDataService;
        private readonly IQueueService _queueService;
        private readonly IIOTControlService _iotControlService;
        private readonly ILogger<PostEnvironmentDataController> _logger;

        public PostEnvironmentDataController(ISensorDataService sensorDataService, IQueueService queueService, IIOTControlService iotControlService, ILogger<PostEnvironmentDataController> logger)
        {
            _sensorDataService = sensorDataService;
            _queueService = queueService;
            _iotControlService = iotControlService;
            _logger = logger;
        }

        [HttpPost]
        // [Authorize(Policy = "MustBeAdmin")]
        public async Task<IActionResult> PostSensorData([FromBody] IOTSensorDataDto data)
        {
            try
            {
                var sensorGoal = await _queueService.DequeueSensorGoalAsync();
                _logger.LogInformation("Received sensor goal for processing: {@SensorGoal}", JsonConvert.SerializeObject(sensorGoal));
                
                // Process incoming sensor data
                SensorData sensorData = new SensorData
                {
                    Temperature = data.Temperature,
                    Humidity = data.Humidity,
                    CO2 = data.CO2,
                    Timestamp = DateTime.Now
                };

                await _sensorDataService.AddSensorDataAsync(sensorData);
                _logger.LogInformation("Sensor data saved: {@SensorData}", JsonConvert.SerializeObject(sensorData));
                
                bool shouldWindowOpen = false;

                if (sensorGoal != null)
                {
                    shouldWindowOpen = _iotControlService.ShouldWindowOpen(
                        sensorData.Temperature, sensorGoal.DesiredTemperature,
                        sensorData.Humidity, sensorGoal.DesiredHumidity,
                        sensorData.CO2, sensorGoal.DesiredCo2
                    );
                }
                
                _logger.LogInformation("Should window open: {ShouldWindowOpen}", shouldWindowOpen);
                
                    return Ok(new
                    {
                        success = true,
                        code = 0,
                        openWindow = shouldWindowOpen
                    });
                return Ok(new { success = true, code = 0 }); // Return zero for IoT device if method is successful
            }
            catch (Exception e)
            {
                Console.WriteLine("Error: " + e.Message);
                // Handle exceptions
                return BadRequest(new { success = false, error = e.Message });
            }
        }
    }
}