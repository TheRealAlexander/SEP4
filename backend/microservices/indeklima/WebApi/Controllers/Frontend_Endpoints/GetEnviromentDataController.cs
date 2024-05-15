using Microsoft.AspNetCore.Mvc;
using WebApi.Models;
using WebApi.Services;

namespace WebApi.Controllers;

[ApiController]
[Route("[controller]")]
public class GetEnvironmentDataController : ControllerBase
{
    private ISensorDataService _sensorDataService;

    public GetEnvironmentDataController(ISensorDataService sensorDataService)
    {
        _sensorDataService = sensorDataService;
    }

    [HttpGet]
    [Authorize(Policy = "MustBeAdmin")]
    public async Task<List<SensorData>> GetSensorData()
    {
        return await _sensorDataService.GetSensorData();
    }
}