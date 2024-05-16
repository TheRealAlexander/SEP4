namespace WebApi.Services;

public class IOTControlService : IIOTControlService
{
    private const double TemperatureThreshold = 1.0; // Threshold
    private const double HumidityThreshold = 3.0; // Threshold
    private const double Co2Threshold = 30.0; // Threshold (in ppm)

    public bool ShouldWindowOpen(double currentTemperature, double desiredTemperature, double currentHumidity, double desiredHumidity, double currentCo2, double desiredCo2)
    {
        bool shouldOpenForTemperature = currentTemperature > (desiredTemperature + TemperatureThreshold);
        bool shouldOpenForHumidity = currentHumidity > (desiredHumidity + HumidityThreshold);
        bool shouldOpenForCo2 = currentCo2 > (desiredCo2 + Co2Threshold);

        // Open the window if any of the conditions are met
        return shouldOpenForTemperature || shouldOpenForHumidity || shouldOpenForCo2;
    }
    
    public bool AreDesiredValuesReached(double currentTemp, double desiredTemp, double currentHumidity, double desiredHumidity, double currentCo2, double desiredCo2)
    {
        bool temperatureReached = currentTemp <= desiredTemp;
        bool humidityReached = currentHumidity <= desiredHumidity;
        bool co2Reached = currentCo2 <= desiredCo2;

        // All desired values need to be reached
        return temperatureReached && humidityReached && co2Reached;
    }
}