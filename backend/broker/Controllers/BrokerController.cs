using Microsoft.AspNetCore.Mvc;

namespace Broker.Controllers
{
    [ApiController]
    [Route("[controller]")]
    public class BrokerController : ControllerBase
    {
        private readonly IBrokerService _brokerService;

        public BrokerController(IBrokerService brokerService)
        {
            _brokerService = brokerService;
        }

        [HttpGet]
        public async Task<List<SensorData>> GetData()
        {
            return await _brokerService.GetAllEnvironmentalDataAsync();
        }
    }
}