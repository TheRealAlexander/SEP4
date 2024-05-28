using MongoDB.Driver;
using WebApi.Models;


namespace WebApi.DAO
{
    public class SensorDataDAO : ISensorDataDAO
    {
        private readonly IMongoCollection<SensorData> _sensorDataMongoCollection;

        
        public SensorDataDAO(MongoDbContext context)
        {
            _sensorDataMongoCollection = context.Database.GetCollection<SensorData>("SensorData");
        }

        public async Task<List<SensorData>> GetSensorDataAsync(int hallId)
        {
            try
            {
                return await _sensorDataMongoCollection.Find(s => s.HallId == hallId).ToListAsync();
            }
            catch (Exception ex)
            {
                throw new NullReferenceException(ex.Message);
            }
        }
        public async Task<List<SensorData>> GetSensorDataAsync(int hallId, int limit)
        {
            try
            {
                return await _sensorDataMongoCollection.Find(s => s.HallId == hallId).Limit(limit).ToListAsync();
            }
            catch (Exception ex)
            {
                throw new NullReferenceException(ex.Message);
            }
        }

        public async Task<List<SensorData>> GetSensorDataAsync(int hallId, DateTime startDate, DateTime endDate)
        {
            try
            {
                var filter = Builders<SensorData>.Filter.And(
                    Builders<SensorData>.Filter.Eq(s => s.HallId, hallId),
                    Builders<SensorData>.Filter.Or(
                        Builders<SensorData>.Filter.And(
                            Builders<SensorData>.Filter.Gte(s => s.TemperatureTimestamp, startDate),
                            Builders<SensorData>.Filter.Lte(s => s.TemperatureTimestamp, endDate)
                        ),
                        Builders<SensorData>.Filter.And(
                            Builders<SensorData>.Filter.Gte(s => s.HumidityTimestamp, startDate),
                            Builders<SensorData>.Filter.Lte(s => s.HumidityTimestamp, endDate)
                        ),
                        Builders<SensorData>.Filter.And(
                            Builders<SensorData>.Filter.Gte(s => s.CO2Timestamp, startDate),
                            Builders<SensorData>.Filter.Lte(s => s.CO2Timestamp, endDate)
                        )
                    )
                );

                return await _sensorDataMongoCollection.Find(filter).ToListAsync();            }
            catch (Exception ex)
            {
                throw new NullReferenceException(ex.Message);
            }
        }

        public async Task AddSensorDataAsync(SensorData sensorData)
        {
            try
            {
                if (sensorData == null)
                {
                    throw new ArgumentNullException(nameof(sensorData));
                }

                // Check for duplicate data
                var duplicateData = await _sensorDataMongoCollection.Find(s => s.HallId == sensorData.HallId && (
                    s.TemperatureTimestamp == sensorData.TemperatureTimestamp ||
                    s.HumidityTimestamp == sensorData.HumidityTimestamp ||
                    s.CO2Timestamp == sensorData.CO2Timestamp)
                ).FirstOrDefaultAsync();
                if (duplicateData != null)
                {
                    throw new Exception("Duplicate data");
                }

                //Add data to the collection
                await _sensorDataMongoCollection.InsertOneAsync(sensorData);
                //Return 0 if successful
                return;
            }
            catch (Exception ex)
            {
                throw new Exception(ex.Message);
            }
        }
        
    }
}