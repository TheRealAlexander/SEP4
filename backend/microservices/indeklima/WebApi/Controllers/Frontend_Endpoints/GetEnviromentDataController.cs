using Microsoft.AspNetCore.Authorization;
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

    
    [HttpGet("{hallId}")]
    [Authorize(Policy = "MustBeAdmin")]
    public async Task<List<SensorData>> GetSensorData(int hallId)
    {
        return await _sensorDataService.GetSensorData(hallId);
    }

    [HttpGet("{hallId}/{limit}")]
    public async Task<List<SensorData>> GetSensorData(int hallId, int limit)
    {
        return await _sensorDataService.GetSensorData(hallId,limit);
    }

    [HttpGet("{hallId}/range")]
    public async Task<List<SensorData>> GetSensorData(int hallId, DateTime startDate, DateTime endDate)
    {
        return await _sensorDataService.GetSensorData(hallId, startDate, endDate);
    }
}