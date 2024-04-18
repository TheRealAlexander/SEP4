
using Microsoft.AspNetCore.Mvc;
using WebApi.Services;

namespace WebApi.Controllers;

[ApiController]
[Route("[controller]")]
public class EnvironmentDataController : ControllerBase
{
    private ISensorDataService _sensorDataService;

    public EnvironmentDataController(ISensorDataService sensorDataService)
    {
        _sensorDataService = sensorDataService;
    }

    [HttpGet]
    public IActionResult GetSensorData()
    {
        return _sensorDataService.GetSensorData();
    }

}