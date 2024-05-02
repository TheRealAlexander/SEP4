using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using sharedObjects.SensorData;

public interface IBrokerService
{
    public Task<List<SensorData>> GetAllEnvironmentalDataAsync();
    //public Task AddSensorData(SensorData sensorData);
}