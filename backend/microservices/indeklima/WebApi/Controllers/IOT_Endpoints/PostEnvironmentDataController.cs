using Microsoft.AspNetCore.Mvc;
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

        public PostEnvironmentDataController(ISensorDataService sensorDataService, ISensorGoalService sensorGoalService, IIOTControlService iotControlService)
        {
            _sensorDataService = sensorDataService;
            _sensorGoalService = sensorGoalService;
            _iotControlService = iotControlService;
        }

        [HttpPost]
        public async Task<IActionResult> PostSensorData([FromBody] IOTSensorDataDto data)
        {
            try
            {
                // Assuming your local time zone is +2 hours (Central European Time - CET)
                TimeZoneInfo localTimeZone = TimeZoneInfo.FindSystemTimeZoneById("Europe/Copenhagen");

                DateTime temperatureTimestamp = TimeZoneInfo.ConvertTime(DateTimeOffset.FromUnixTimeSeconds(data.Temperature_ts).UtcDateTime, localTimeZone);
                DateTime humidityTimestamp = TimeZoneInfo.ConvertTime(DateTimeOffset.FromUnixTimeSeconds(data.Humidity_ts).UtcDateTime, localTimeZone);
                DateTime co2Timestamp = TimeZoneInfo.ConvertTime(DateTimeOffset.FromUnixTimeSeconds(data.Co2_ts).UtcDateTime, localTimeZone);
                
                // Get sensor goal for the current hallId
                SensorGoal? sensorGoal = await _sensorGoalService.GetSensorGoalAsync(data.HallId);
                
                // Process incoming sensor data
                SensorData sensorData = new SensorData
                {
                    HallId = data.HallId,
                    Temperature = data.Temperature,
                    Humidity = data.Humidity,
                    CO2 = data.CO2,
                    TemperatureTimestamp = temperatureTimestamp,
                    HumidityTimestamp = humidityTimestamp,
                    CO2Timestamp = co2Timestamp
                };

                await _sensorDataService.AddSensorDataAsync(sensorData);

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