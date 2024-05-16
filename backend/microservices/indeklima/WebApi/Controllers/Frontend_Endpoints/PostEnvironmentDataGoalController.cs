using System.Threading.Tasks;
using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Mvc;
using WebApi.Models;
using WebApi.Services;

namespace WebApi.Controllers
{
    [ApiController]
    [Route("[controller]")]
    public class PostEnvironmentDataGoalController : ControllerBase
    {
        private readonly ISensorGoalService _sensorGoalService;

        public PostEnvironmentDataGoalController(ISensorGoalService sensorGoalService)
        {
            _sensorGoalService = sensorGoalService;
        }

        [HttpPost]
        [Authorize(Policy = "MustBeAdmin")]
        public async Task<IActionResult> PostSensorDataGoal([FromBody] SensorGoal sensorGoal)
        {
            try
            {
                await _sensorGoalService.AddOrUpdateSensorGoalAsync(sensorGoal);
                return Ok(new
                {
                    success = true,
                    hallId = sensorGoal.HallId,
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