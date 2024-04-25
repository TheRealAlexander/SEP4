namespace WebApi.DAO
{
    public interface ISensorDataDAO
    {
         Task<List<SensorData>> GetSensorDataAsync();
        Task AddSensorDataAsync(SensorData sensorData);
    }
}