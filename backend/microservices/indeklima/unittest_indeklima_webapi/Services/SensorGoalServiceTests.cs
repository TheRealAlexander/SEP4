using Moq;
using WebApi.DAO;
using WebApi.Models;
using WebApi.Services;

namespace unittest_indeklima_webapi.Services
{
    public class SensorGoalServiceTests
    {
        private readonly Mock<ISensorGoalDAO> _mockSensorGoalDao;
        private readonly SensorGoalService _service;

        public SensorGoalServiceTests()
        {
            _mockSensorGoalDao = new Mock<ISensorGoalDAO>();
            _service = new SensorGoalService(_mockSensorGoalDao.Object);
        }

        [Fact]
        public async Task GetSensorGoalAsync_ReturnsExpectedData()
        {
            // Arrange
            var expectedSensorGoal = new SensorGoal();
            _mockSensorGoalDao.Setup(dao => dao.GetSensorGoalAsync(It.IsAny<int>())).ReturnsAsync(expectedSensorGoal);

            // Act
            var result = await _service.GetSensorGoalAsync(1);

            // Assert
            Assert.Equal(expectedSensorGoal, result);
        }

        [Fact]
        public async Task GetSensorGoalAsync_ThrowsException_WhenDaoThrowsException()
        {
            // Arrange
            _mockSensorGoalDao.Setup(dao => dao.GetSensorGoalAsync(It.IsAny<int>())).ThrowsAsync(new Exception("DAO error"));

            // Act & Assert
            var exception = await Assert.ThrowsAsync<Exception>(() => _service.GetSensorGoalAsync(1));
            Assert.Equal("Error retrieving sensor goal: DAO error", exception.Message);
        }

        [Fact]
        public async Task AddOrUpdateSensorGoalAsync_CallsDao_WhenSensorGoalIsValid()
        {
            // Arrange
            var sensorGoal = new SensorGoal();

            // Act
            await _service.AddOrUpdateSensorGoalAsync(sensorGoal);

            // Assert
            _mockSensorGoalDao.Verify(dao => dao.AddOrUpdateSensorGoalAsync(sensorGoal), Times.Once);
        }

        [Fact]
        public async Task AddOrUpdateSensorGoalAsync_ThrowsException_WhenDaoThrowsException()
        {
            // Arrange
            var sensorGoal = new SensorGoal();
            _mockSensorGoalDao.Setup(dao => dao.AddOrUpdateSensorGoalAsync(sensorGoal)).ThrowsAsync(new Exception("DAO error"));

            // Act & Assert
            var exception = await Assert.ThrowsAsync<Exception>(() => _service.AddOrUpdateSensorGoalAsync(sensorGoal));
            Assert.Equal("Error adding or updating sensor goal: DAO error", exception.Message);
        }

        [Fact]
        public async Task DeleteSensorGoalAsync_CallsDao_WhenHallIdIsValid()
        {
            // Arrange
            var hallId = 1;

            // Act
            await _service.DeleteSensorGoalAsync(hallId);

            // Assert
            _mockSensorGoalDao.Verify(dao => dao.DeleteSensorGoalAsync(hallId), Times.Once);
        }

        [Fact]
        public async Task DeleteSensorGoalAsync_ThrowsException_WhenDaoThrowsException()
        {
            // Arrange
            var hallId = 1;
            _mockSensorGoalDao.Setup(dao => dao.DeleteSensorGoalAsync(hallId)).ThrowsAsync(new Exception("DAO error"));

            // Act & Assert
            var exception = await Assert.ThrowsAsync<Exception>(() => _service.DeleteSensorGoalAsync(hallId));
            Assert.Equal("Error deleting sensor goal: DAO error", exception.Message);
        }
    }
}
