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

    [HttpGet("GetSensorData/{dateTime1}/{dateTime2}")]
    public async Task<SensorData> GetSensorData(DateTime dateTime1, DateTime dateTime2)
    {
        return await _brokerService.GetSensorData(dateTime1, dateTime2);
    }

    [HttpPost("SetPrefClimateValues/{temp}/{humidity}")]
    public async Task SetPrefClimateValues(int temp, int humidity)
    {
        await _brokerService.SetPrefClimateValues(temp, humidity);
    }

}