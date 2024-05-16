using Newtonsoft.Json;

namespace SharedObjects.Models
{
    public class SensorGoal
    {
        [BsonId]
        [BsonRepresentation(MongoDB.Bson.BsonType.ObjectId)]
        public string Id { get; set; } = ObjectId.GenerateNewId().ToString();
        [JsonProperty("hallId")]
        public int HallId { get; set; }
        [JsonProperty("desiredTemperature")]
        public double DesiredTemperature { get; set; }
        [JsonProperty("desiredHumidity")]
        public double DesiredHumidity { get; set; }
        [JsonProperty("desiredCO2")]
        public double DesiredCo2 { get; set; }
    }
}