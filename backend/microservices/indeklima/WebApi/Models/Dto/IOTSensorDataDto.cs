namespace WebApi.Models.Dto
{
    public class IOTSensorDataDto
    {
        public int HallId { get; set; }
        public double Temperature { get; set; }
        public double Humidity { get; set; }
        public double CO2 { get; set; }
        public long Temperature_ts { get; set; } // Name needs to match the json object IoT sends
        public long Humidity_ts { get; set; } // Name needs to match the json object IoT sends
        public long Co2_ts { get; set; } // Name needs to match the json object IoT sends
    }
}
