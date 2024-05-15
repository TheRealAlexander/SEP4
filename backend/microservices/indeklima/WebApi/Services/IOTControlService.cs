namespace WebApi.Services;

public class IOTControlService : IIOTControlService
{
    private const double TemperatureThreshold = 2.0; // Example threshold
    private const double HumidityThreshold = 10.0; // Example threshold
    private const double Co2Threshold = 50.0; // Example threshold (in ppm)

    public bool ShouldWindowOpen(double currentTemperature, double desiredTemperature, double currentHumidity, double desiredHumidity, double currentCo2, double desiredCo2)
    {
        bool shouldOpenForTemperature = currentTemperature > (desiredTemperature + TemperatureThreshold);
        bool shouldOpenForHumidity = currentHumidity > (desiredHumidity + HumidityThreshold);
        bool shouldOpenForCo2 = currentCo2 > (desiredCo2 + Co2Threshold);

        // Open the window if any of the conditions are met
        return shouldOpenForTemperature || shouldOpenForHumidity || shouldOpenForCo2;
    }
}