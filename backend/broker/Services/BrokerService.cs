using System.Net.Http;
using System.Threading.Tasks;

public class BrokerService : IBrokerService
{
    private readonly HttpClient _httpClient;

    public BrokerService(HttpClient httpClient)
    {
        _httpClient = httpClient;
    }

    public async Task<string> GetAllEnvironmentalDataAsync()
    {
        var response = await _httpClient.GetAsync("http://localhost:5200/GetEnvironmentalData");

        response.EnsureSuccessStatusCode();

        return await response.Content.ReadAsStringAsync();
    }
}