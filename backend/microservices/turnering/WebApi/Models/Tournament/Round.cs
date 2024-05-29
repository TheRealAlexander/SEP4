namespace WebApi.Models;

public class Round
{
    public int RoundNumber;
    public List<Court> Courts { get; set; }

    public Round(int roundNumber)
    {
        Courts = new List<Court>();
        RoundNumber = roundNumber;
    }
}