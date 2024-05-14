using System.Threading.Tasks;
using Microsoft.AspNetCore.Authorization;
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
        private readonly ISensorDataService _sensorDataService;

        public PostEnviromentDataController(ISensorDataService sensorDataService)
        {
            _sensorDataService = sensorDataService;
        }

        [HttpPost]
        [Authorize(Policy = "MustBeAdmin")]
        public async Task<IActionResult> PostSensorData([FromBody] IOTSensorDataDto data)
        {
            try
            {
                // Process incoming sensor data
                SensorData sensorData = new SensorData
                {
                    Temperature = data.Temperature,
                    Humidity = data.Humidity,
                    Timestamp = DateTime.Now
                };

                await _sensorDataService.AddSensorDataAsync(sensorData);
                SensorGoal latestSensorGoal = await _sensorDataService.GetSensorDataGoalAsync();
                
                return Ok(new
                {
                    success = true,
                    sensorGoal = latestSensorGoal
                });
            }
            catch (Exception e)
            {
                // Handle exceptions
                return BadRequest(new { success = false, error = e.Message });
            }
        }
    }
}