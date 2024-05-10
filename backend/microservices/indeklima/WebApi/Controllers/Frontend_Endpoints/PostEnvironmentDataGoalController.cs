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
        private readonly ISensorDataService _sensorDataService;

        public PostEnvironmentDataGoalController(ISensorDataService sensorDataService)
        {
            _sensorDataService = sensorDataService;
        }

        [HttpPost]
        [Authorize(Policy = "MustBeAdmin")]
        public async Task<IActionResult> PostSensorDataGoal(SensorGoal sensorGoal)
        {
            try
            {
                await _sensorDataService.AddSensorDataGoalAsync(sensorGoal);
                
                return Ok(new { success = true });
            }
            catch (Exception e)
            {
                return BadRequest(new { success = false, error = e.Message });
            }
        }
    }
}