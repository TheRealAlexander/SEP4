using System.Threading.Tasks;
using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Mvc;
using Newtonsoft.Json;
using WebApi.Models;
using WebApi.Services;

namespace WebApi.Controllers
{
    [ApiController]
    [Route("[controller]")]
    public class PostEnvironmentDataGoalController : ControllerBase
    {
        private readonly IQueueService _queueService;

        public PostEnvironmentDataGoalController(IQueueService queueService)
        {
            _queueService = queueService;
        }

        [HttpPost]
        // [Authorize(Policy = "MustBeAdmin")]
        public async Task<IActionResult> PostSensorDataGoal([FromBody] SensorGoal sensorGoal)
        {
            try
            {
                await _queueService.EnqueueSensorGoalAsync(sensorGoal);
                return Ok(new
                {
                    success = true,
                    desiredTemperature = sensorGoal.DesiredTemperature,
                    desiredHumidity = sensorGoal.DesiredHumidity,
                    desiredCo2 = sensorGoal.DesiredCo2
                });
            }
            catch (Exception e)
            {
                return BadRequest(new { success = false, error = e.Message });
            }
        }
    }
}