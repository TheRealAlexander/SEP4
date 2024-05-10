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

    [HttpGet("GetSensorData")]
    public async Task<List<SensorData>> GetSensorData()
    {
        return await _brokerService.GetSensorData();
    }

}