using Microsoft.AspNetCore.Mvc;
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
        public IActionResult GetSensorData()
        {
            //TODO: Implement
            throw new NotImplementedException();
        }
    }
}
