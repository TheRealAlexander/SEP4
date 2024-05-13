﻿using MongoDB.Driver;
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
            try
            {
                if (sensorData == null)
                {
                    throw new ArgumentNullException(nameof(sensorData));
                }

                //Check for dubplicate data
                var duplicateData = await _sensorDataMongoCollection.Find(s => s.Timestamp == sensorData.Timestamp)
                    .FirstOrDefaultAsync();
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