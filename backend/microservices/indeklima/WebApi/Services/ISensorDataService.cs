using Microsoft.AspNetCore.Mvc;
using Microsoft.Extensions.Diagnostics.HealthChecks;

namespace WebApi.Services
{
    public interface ISensorDataService
    {
        public IActionResult GetSensorData();
    }
}
