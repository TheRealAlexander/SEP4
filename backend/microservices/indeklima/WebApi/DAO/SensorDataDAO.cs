using MongoDB.Driver;
using WebApi.Models;

namespace WebApi.DAO
{
    public class SensorDataDao : ISensorDataDAO
    {
        private readonly IMongoCollection<SensorData> _sensorDataMongoCollection;
        private readonly IMongoCollection<SensorGoal> _sensorGoalMongoCollection;

        public SensorDataDao(MongoDbContext context)
        {
            _sensorDataMongoCollection = context.Database.GetCollection<SensorData>("SensorData");
            _sensorGoalMongoCollection = context.Database.GetCollection<SensorGoal>("SensorGoal");
        }

        public async Task<List<SensorData>> GetSensorDataAsync()
        {
            try
            {
                return await _sensorDataMongoCollection.Find(s => true).ToListAsync();
            }
            catch (Exception ex)
            {
                throw new NullReferenceException(ex.Message);
            }
        }

        public async Task AddSensorDataAsync(SensorData sensorData)
        {
            await _sensorDataMongoCollection.InsertOneAsync(sensorData);
        }

        public async Task AddSensorDataGoalAsync(SensorGoal sensorGoal)
        {
            await _sensorGoalMongoCollection.InsertOneAsync(sensorGoal);
        }

        public async Task<SensorGoal> GetLatestSensorGoalAsync()
        {
            try
            {
                return await _sensorGoalMongoCollection.Find(s => true).SortByDescending(s => s.Timestamp)
                    .FirstOrDefaultAsync();
            }
            catch (Exception ex)
            {
                throw new NullReferenceException(ex.Message);
            }
        }
    }
}