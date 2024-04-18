using Microsoft.EntityFrameworkCore;
using WebApi.Models;

namespace WebApi.DAO
{
    public class SensorDataDao
    {
        private readonly DbContextPostgres _context;

        public SensorDataDao(DbContextPostgres context)
        {
            _context = context;
        }

        public async Task<List<SensorData>> GetSensorDataAsync()
        {
            try
            {
                return await _context.SensorData.ToListAsync();
            }
            catch (Exception ex)
            {
                throw new NullReferenceException(ex.Message);
            }
        }
    }
}
