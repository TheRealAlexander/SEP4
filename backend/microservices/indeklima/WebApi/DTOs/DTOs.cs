namespace DefaultNamespace;

public class DTOs
{
    public record Temperature(double Value, string Unit);
    public record Humidity(double Value, string Unit);
    public record CO2(double Value, string Unit);
}