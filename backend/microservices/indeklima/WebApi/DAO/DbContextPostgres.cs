using Microsoft.EntityFrameworkCore;
using WebApi.Models;

namespace WebApi.DAO
{
    public class DbContextPostgres : DbContext
    {
        public DbContextPostgres(DbContextOptions<DbContextPostgres> options) : base(options)
        {
        }

        public DbSet<SensorData>? SensorData { get; set; }

        protected override void OnModelCreating(ModelBuilder modelBuilder)
        {
            // Auto increment the ID
            modelBuilder.Entity<SensorData>().Property(p => p.Id).ValueGeneratedOnAdd();

            // Seed the SensorData table with dummy data on model creation
            modelBuilder.Entity<SensorData>().HasData(
                new SensorData
                {
                    Id = 1,
                    Temperature = 20.0,
                    Humidity = 50.0,
                    CO2 = 400.0,
                    Timestamp = new DateTime(2021, 1, 1, 0, 0, 0)
                },
                new SensorData
                {
                    Id = 2,
                    Temperature = 21.0,
                    Humidity = 51.0,
                    CO2 = 401.0,
                    Timestamp = new DateTime(2021, 1, 1, 0, 1, 0)
                }
            );
        }
    }
}