
using Microsoft.AspNetCore.Mvc;
using WebApi.Models;
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
    public async Task<List<SensorData>> GetSensorData()
    {
        return await _sensorDataService.GetSensorData();
    }

}