using DefaultNamespace;

namespace WebApi.Services;

public interface ITemperatureLogic
{
    public Task<DTOs.Temperature> GetTemperatureAsync();
}