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
        private readonly ISensorGoalService _sensorGoalService;
        private readonly IIOTControlService _iotControlService;
        private readonly ILogger<PostEnvironmentDataController> _logger;

        public PostEnvironmentDataController(ISensorDataService sensorDataService, ISensorGoalService sensorGoalService, IIOTControlService iotControlService, ILogger<PostEnvironmentDataController> logger)
        {
            _sensorDataService = sensorDataService;
            _sensorGoalService = sensorGoalService;
            _iotControlService = iotControlService;
            _logger = logger;
        }

        [HttpPost]
        // [Authorize(Policy = "MustBeAdmin")]
        public async Task<IActionResult> PostSensorData([FromBody] IOTSensorDataDto data)
        {
            try
            {
                _logger.LogInformation("Received sensor data: {@Data}", JsonConvert.SerializeObject(data));
                
                // Get sensor goal for the current hallId
                SensorGoal? sensorGoal = await _sensorGoalService.GetSensorGoalAsync(data.HallId);
                _logger.LogInformation("Fetched sensor goal for HallId {HallId}: {@SensorGoal}", data.HallId, JsonConvert.SerializeObject(sensorGoal));
                
                // Process incoming sensor data
                SensorData sensorData = new SensorData
                {
                    HallId = data.HallId,
                    Temperature = data.Temperature,
                    Humidity = data.Humidity,
                    CO2 = data.CO2,
                    Timestamp = DateTime.Now
                };

                await _sensorDataService.AddSensorDataAsync(sensorData);
                _logger.LogInformation("Sensor data saved: {@SensorData}", JsonConvert.SerializeObject(sensorData));

                bool? shouldWindowOpen = null;

                if (sensorGoal != null && sensorGoal.HallId == data.HallId)
                {
                    if (_iotControlService.AreDesiredValuesReached(
                            sensorData.Temperature, sensorGoal.DesiredTemperature,
                            sensorData.Humidity, sensorGoal.DesiredHumidity,
                            sensorData.CO2, sensorGoal.DesiredCo2))
                    {
                        shouldWindowOpen = false;
                        await _sensorGoalService.DeleteSensorGoalAsync(data.HallId);
                    }
                    else
                    {
                        shouldWindowOpen = _iotControlService.ShouldWindowOpen(
                            sensorData.Temperature, sensorGoal.DesiredTemperature,
                            sensorData.Humidity, sensorGoal.DesiredHumidity,
                            sensorData.CO2, sensorGoal.DesiredCo2
                        );
                    }
                }
                
                _logger.LogInformation("Should window open: {ShouldWindowOpen}", shouldWindowOpen);

                return Ok(new
                {
                    success = true,
                    code = 0, // Return zero for IoT device if method is successful
                    hallId = data.HallId,
                    openWindow = shouldWindowOpen ?? false
                });
                
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