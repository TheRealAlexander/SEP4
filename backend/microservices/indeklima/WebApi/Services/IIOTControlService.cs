namespace WebApi.Services;

public interface IIOTControlService
{
    bool ShouldWindowOpen(double currentTemp, double desiredTemp, double currentHumidity,
        double desiredHumidity, double currentCo2, double desiredCo2);
    bool AreDesiredValuesReached(double currentTempe, double desiredTempe, double currentHumidity,
        double desiredHumidity, double currentCo2, double desiredCo2);

}