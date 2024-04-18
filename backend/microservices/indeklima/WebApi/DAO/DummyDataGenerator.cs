using WebApi.Models;

namespace WebApi.DAO
{
    public static class DummyDataGenerator
    {
        public static List<SensorData> GenerateDummySensorData(int count)
        {
            var sensorDataList = new List<SensorData>();
            var random = new Random();

            // Generate dummy data for the specified count
            for (int i = 0; i < count; i++)
            {
                var temperature = new Temperature { Value = random.Next(18, 32) }; // Random temperature between 18 and 32 degrees Celsius
                var humidity = new Humidity { Value = random.Next(30, 70) }; // Random humidity between 30% and 70%
                var co2 = new CO2 { Value = random.Next(300, 1000) }; // Random CO2 level between 300 and 1000 ppm
                var timestamp = TimeSpan.FromMinutes(-(i * 5)); // Generate timestamps for the last 5 minutes

                var sensorData = new SensorData
                {
                    Temperature = temperature,
                    Humidity = humidity,
                    CO2 = co2,
                    Timestamp = timestamp
                };

                sensorDataList.Add(sensorData);
            }

            return sensorDataList;
        }
    }
}