using Microsoft.EntityFrameworkCore;
using WebApi.Models;

namespace WebApi.DAO
{
    public class DbContextPostgres : DbContext
    {
        public DbContextPostgres(DbContextOptions<DbContextPostgres> options) : base(options)
        {
        }
        protected override void OnModelCreating(ModelBuilder modelBuilder)
        {
            // Seed the SensorData table with dummy data on model creation
            modelBuilder.Entity<SensorData>().HasData(DummyDataGenerator.GenerateDummySensorData(10)); // Adjust count as needed
        }
        public DbSet<SensorData> SensorData { get; set; }
    }
}
