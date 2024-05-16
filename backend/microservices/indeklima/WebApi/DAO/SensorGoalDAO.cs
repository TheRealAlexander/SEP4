using MongoDB.Driver;
using WebApi.Models;

namespace WebApi.DAO
{
    public class SensorGoalDAO : ISensorGoalDAO
    {
        private readonly IMongoCollection<SensorGoal> _sensorGoalCollection;

        public SensorGoalDAO(MongoDbContext context)
        {
            _sensorGoalCollection = context.Database.GetCollection<SensorGoal>("SensorGoals");
        }

        public async Task<SensorGoal?> GetSensorGoalAsync(int hallId)
        {
            return await _sensorGoalCollection.Find(g => g.HallId == hallId).FirstOrDefaultAsync();
        }

        public async Task AddOrUpdateSensorGoalAsync(SensorGoal sensorGoal)
        {
            // Find the existing goal by hallId
            var existingGoal = await _sensorGoalCollection.Find(g => g.HallId == sensorGoal.HallId).FirstOrDefaultAsync();

            if (existingGoal != null)
            {
                // Update fields while retaining the original Id
                existingGoal.DesiredTemperature = sensorGoal.DesiredTemperature;
                existingGoal.DesiredHumidity = sensorGoal.DesiredHumidity;
                existingGoal.DesiredCo2 = sensorGoal.DesiredCo2;

                // Replace the existing document with the updated one
                await _sensorGoalCollection.ReplaceOneAsync(
                    g => g.Id == existingGoal.Id,
                    existingGoal,
                    new ReplaceOptions { IsUpsert = true }
                );
            }
            else
            {
                // Insert as new document if no existing document is found
                await _sensorGoalCollection.InsertOneAsync(sensorGoal);
            }
        }
        
        public async Task DeleteSensorGoalAsync(int hallId)
        {
            await _sensorGoalCollection.DeleteOneAsync(g => g.HallId == hallId);
        }
    }
}