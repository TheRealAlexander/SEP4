namespace WebApi.Models
{
    public class SensorData
    {
        public int Id { get; set; }
        public Temperature Temperature { get; set; }
        public Humidity Humidity { get; set; }
        public CO2 CO2 { get; set; }
        public TimeSpan Timestamp { get; set; }
    }
}
