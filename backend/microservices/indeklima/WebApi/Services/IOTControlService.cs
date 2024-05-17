namespace WebApi.Services;

public class IOTControlService : IIOTControlService
{
    
    public bool ShouldWindowOpen(double currentTemperature, double desiredTemperature, double currentHumidity, double desiredHumidity, double currentCo2, double desiredCo2)
    {
        bool shouldOpenForTemperature = currentTemperature > desiredTemperature;
        bool shouldOpenForHumidity = currentHumidity > desiredHumidity;
        bool shouldOpenForCo2 = currentCo2 > desiredCo2;

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