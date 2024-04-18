namespace WebApi.Models
{
    public class SensorData
    {
        public int Id { get; set; }
        public double Temperature { get; set; }
        public double Humidity { get; set; }
        public double CO2 { get; set; }
        public DateTime Timestamp { get; set; }
    }
}