using WebApi.Services;

namespace unittest_indeklima_webapi.Services;

public class IOTControlServiceTests
{
    private readonly IOTControlService _iotControlService;

    public IOTControlServiceTests()
    {
        _iotControlService = new IOTControlService();
    }

    [Fact]
    public void ShouldWindowOpen_ReturnsTrue_WhenCurrentTemperatureIsAboveDesired()
    {
        // Arrange
        double currentTemperature = 25;
        double desiredTemperature = 22;
        double currentHumidity = 30;
        double desiredHumidity = 50;
        double currentCo2 = 400;
        double desiredCo2 = 600;

        // Act
        bool result = _iotControlService.ShouldWindowOpen(currentTemperature, desiredTemperature, currentHumidity, desiredHumidity, currentCo2, desiredCo2);

        // Assert
        Assert.True(result);
    }

    [Fact]
    public void ShouldWindowOpen_ReturnsTrue_WhenCurrentHumidityIsAboveDesired()
    {
        // Arrange
        double currentTemperature = 20;
        double desiredTemperature = 22;
        double currentHumidity = 60;
        double desiredHumidity = 50;
        double currentCo2 = 400;
        double desiredCo2 = 600;

        // Act
        bool result = _iotControlService.ShouldWindowOpen(currentTemperature, desiredTemperature, currentHumidity, desiredHumidity, currentCo2, desiredCo2);

        // Assert
        Assert.True(result);
    }

    [Fact]
    public void ShouldWindowOpen_ReturnsTrue_WhenCurrentCo2IsAboveDesired()
    {
        // Arrange
        double currentTemperature = 20;
        double desiredTemperature = 22;
        double currentHumidity = 30;
        double desiredHumidity = 50;
        double currentCo2 = 700;
        double desiredCo2 = 600;

        // Act
        bool result = _iotControlService.ShouldWindowOpen(currentTemperature, desiredTemperature, currentHumidity, desiredHumidity, currentCo2, desiredCo2);

        // Assert
        Assert.True(result);
    }

    [Fact]
    public void ShouldWindowOpen_ReturnsFalse_WhenAllValuesAreBelowDesired()
    {
        // Arrange
        double currentTemperature = 20;
        double desiredTemperature = 22;
        double currentHumidity = 30;
        double desiredHumidity = 50;
        double currentCo2 = 400;
        double desiredCo2 = 600;

        // Act
        bool result = _iotControlService.ShouldWindowOpen(currentTemperature, desiredTemperature, currentHumidity, desiredHumidity, currentCo2, desiredCo2);

        // Assert
        Assert.False(result);
    }

    [Fact]
    public void AreDesiredValuesReached_ReturnsTrue_WhenAllValuesAreAtOrBelowDesired()
    {
        // Arrange
        double currentTemperature = 20;
        double desiredTemperature = 22;
        double currentHumidity = 30;
        double desiredHumidity = 50;
        double currentCo2 = 400;
        double desiredCo2 = 600;

        // Act
        bool result = _iotControlService.AreDesiredValuesReached(currentTemperature, desiredTemperature, currentHumidity, desiredHumidity, currentCo2, desiredCo2);

        // Assert
        Assert.True(result);
    }

    [Fact]
    public void AreDesiredValuesReached_ReturnsFalse_WhenAnyValueIsAboveDesired()
    {
        // Arrange
        double currentTemperature = 25;
        double desiredTemperature = 22;
        double currentHumidity = 30;
        double desiredHumidity = 50;
        double currentCo2 = 400;
        double desiredCo2 = 600;

        // Act
        bool result = _iotControlService.AreDesiredValuesReached(currentTemperature, desiredTemperature, currentHumidity, desiredHumidity, currentCo2, desiredCo2);

        // Assert
        Assert.False(result);
    }
}
