using MongoDB.Bson;
using MongoDB.Bson.Serialization.Attributes;

namespace SharedObjects.Models
{
    public class User {
        [BsonId]
        [BsonRepresentation(MongoDB.Bson.BsonType.ObjectId)]
        private string _id = ObjectId.GenerateNewId().ToString();
        public string Username { get; set; }  = string.Empty;
        public string Password { get; set; }  = string.Empty;
        public string Email { get; set; }  = string.Empty;
        public string Role { get; set; }  = string.Empty;
        public int Age { get; set; }
    }
}