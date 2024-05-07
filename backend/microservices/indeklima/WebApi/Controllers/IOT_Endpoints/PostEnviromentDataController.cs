﻿using Microsoft.AspNetCore.Mvc;
using WebApi.Models;
using WebApi.Models.Dto;
using WebApi.Services;

namespace WebApi.Controllers
{
    [ApiController]
    [Route("[controller]")]
    public class PostEnviromentDataController : ControllerBase
    {
        private ISensorDataService _sensorDataService;

        public PostEnviromentDataController(ISensorDataService sensorDataService)
        {
            _sensorDataService = sensorDataService;
        }

        [HttpPost]
        [Authorize(Policy = "MustBeAdmin")]
        public IActionResult PostSensorData(IOTSensorDataDto data)
        {
            try
            {
                SensorData sensorData = new SensorData
                {
                    Temperature = data.Temperature,
                    Humidity = data.Humidity,
                    Timestamp = DateTime.Now
                };

                _sensorDataService.AddSensorData(sensorData);

                return Ok(sensorData); // Return zero for IoT device if method is successful
            }
            catch (Exception e)
            {
                return BadRequest(new { success = false, error = e.Message });
            }
        }
    }
}