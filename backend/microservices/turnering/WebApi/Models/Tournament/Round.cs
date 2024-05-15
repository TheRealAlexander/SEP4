namespace WebApi.Models;

public class Round
{
    public List<Court> Courts { get; set; }

    public Round()
    {
        Courts = new List<Court>();
    }
}