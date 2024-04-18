using Microsoft.EntityFrameworkCore;
using WebApi.Models;

namespace WebApi.DAO
{
    public class SensorDataDao
    {
        private readonly DbContextPostgres _context;

        public SensorDataDao(DbContextPostgres context)
        {
            _context = context;
        }

        public async Task<List<SensorData>> GetSensorDataAsync()
        {
            try
            {
                var sensorDataList = new List<SensorData>();

                // Create a single instance of SensorData with the specified values
                var sensorData = new SensorData
                {
                    Id = 1,
                    Temperature = 20.0,
                    Humidity = 50.0,
                    CO2 = 400.0,
                    Timestamp = new DateTime(2021, 1, 1, 0, 0, 0)
                };

                // Add the single instance to the list
                sensorDataList.Add(sensorData);

                return sensorDataList; 


                //TODO: Implement the logic to retrieve the SensorData from the database
                return await _context.SensorData.ToListAsync();
            }
            catch (Exception ex)
            {
                throw new NullReferenceException(ex.Message);
            }
        }
    }
}
