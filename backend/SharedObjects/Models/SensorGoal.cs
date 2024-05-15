using Newtonsoft.Json;

namespace SharedObjects.Models
{
    public class SensorGoal
    {
        [JsonProperty("desiredTemperature")]
        public double DesiredTemperature { get; set; }
        [JsonProperty("desiredHumidity")]
        public double DesiredHumidity { get; set; }
        [JsonProperty("desiredCO2")]
        public double DesiredCo2 { get; set; }
    }
}