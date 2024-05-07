namespace DefaultNamespace;

[ApiController]
[Route("[controller]")
public class PostEnvironmentDataGoalController : ControllerBase
{
    private ISensorDataService _sensorDataService;
    
    public PostEnvironmentDataGoalController(ISensorDataService sensorDataService)
    {
        _sensorDataService = sensorDataService;
    }
    
    [HttpPost]
    [Authorize(Policy = "MustBeAdmin")]
    public IActionResult PostSensorDataGoal(SensorGoal sensorGoal)
    {
        try
        {
            _sensorDataService.AddSensorDataGoal(sensorGoal);
            SensorGoal newSensorDataGoal = _sensorDataService.GetSensorDataGoal();
            if (newSensorDataGoal != null)
            {
                return Ok(newSensorDataGoal); // Return the new sensor data if method is successful
            }
            return Ok(0); // Return zero for IoT device if method is successful
        }
        catch (Exception e)
        {
            return BadRequest(new { success = false, error = e.Message });
        }
    }
}