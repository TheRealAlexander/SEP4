using MongoDB.Bson;
using MongoDB.Bson.Serialization.Attributes;


public class User {
    [BsonId]
    [BsonRepresentation(MongoDB.Bson.BsonType.ObjectId)]
    private string _id = ObjectId.GenerateNewId().ToString();
    public string Username { get; set; }
    public string Password { get; set; }
    public string Email { get; set; }
    public string Role { get; set; }
    public int Age { get; set; }
}