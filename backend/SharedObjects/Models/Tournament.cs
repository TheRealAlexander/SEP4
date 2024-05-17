using MongoDB.Bson;
using MongoDB.Bson.Serialization.Attributes;
using System.Collections.Generic;

namespace SharedObjects.Models
{
    public class Tournament
    {
        [BsonId]
        [BsonRepresentation(MongoDB.Bson.BsonType.ObjectId)]
        public string TournamentID { get; set; } = ObjectId.GenerateNewId().ToString();
        public int State { get; set; }
        public DateTime TimeAndDate { get; set; }
        public string Description { get; set; } = string.Empty;
        public int FieldCount { get; set; }
        public string Format { get; set; }  = string.Empty;
        public ICollection<string?> Participants { get; set; } = new List<string?>();

    }
}
