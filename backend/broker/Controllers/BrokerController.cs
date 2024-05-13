using Microsoft.AspNetCore.Mvc;
using SharedObjects.Models;
using Broker.Services;

namespace WebApi.Controllers;

[ApiController]
[Route("[controller]")]
public class BrokerController : ControllerBase
{
    private IBrokerService _brokerService;

    public BrokerController(IBrokerService brokerService)
    {
        _brokerService = brokerService;
    }

    [HttpGet("GetSensorData/{limit}")]
    public async Task<List<SensorData>> GetSensorData(int limit)
    {
        return await _brokerService.GetSensorData(limit);
    }

    [HttpGet("GetSensorData")]
    public async Task<SensorData> GetSensorData([FromQuery] DateTime dateTime1, [FromQuery] DateTime dateTime2)
    {
        return await _brokerService.GetSensorData(dateTime1, dateTime2);
    }

    [HttpPost("SetPrefClimateValues")]
    public async Task SetPrefClimateValues([FromQuery] int temp, [FromQuery] int humidity)
    {
        await _brokerService.SetPrefClimateValues(temp, humidity);
    }

}