using DefaultNamespace;
using Microsoft.AspNetCore.Mvc;
using WebApi.Services;

namespace WebApi.Controllers;

[ApiController]
[Route("[controller]")]
public class TemperatureController : ControllerBase
{
    private readonly ITemperatureLogic _temperatureLogic;

    public TemperatureController(ITemperatureLogic temperatureLogic)
    {
        _temperatureLogic = temperatureLogic;
    }

    [HttpGet]
    public async Task<ActionResult<DTOs.Temperature>> GetTemperatureAsync()
    {
        try
        {
            var temperature = await _temperatureLogic.GetTemperatureAsync();
            return Ok(temperature);
        }
        catch (Exception e)
        {
            return StatusCode(500, e.Message);
        }
    }
}