﻿namespace WebApi.Models.Dto
{
    public class IOTSensorDataDto
    {
        public int HallId { get; set; }
        public double Temperature { get; set; }
        public double Humidity { get; set; }
        public double CO2 { get; set; }
    }
}
