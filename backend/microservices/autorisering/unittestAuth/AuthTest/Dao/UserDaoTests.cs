﻿namespace AuthTest
{
    using Xunit;
    using MongoDB.Driver;
    using System;
    using System.Data;
    using System.Threading.Tasks;
    using WebApi.Models;
    using WebApi.DAO;

    public class UserDaoTests : IAsyncLifetime
    {
        private readonly UserDAO _dao;
        private readonly IMongoDatabase _database;

        public UserDaoTests()
        {
            var connectionString = "mongodb://localhost:27017"; // Adjust as necessary for your environment
            var client = new MongoClient(connectionString);
            _database = client.GetDatabase("BackendTestAuthDB");
            _dao = new UserDAO(new MongoDbContext(connectionString, "BackendTestAuthDB"));
        }

        public async Task InitializeAsync()
        {
            // Clean up the user collection before each test
            await _database.DropCollectionAsync("UserData");
        }

        public Task DisposeAsync()
        {
            // No explicit cleanup needed after tests
            return Task.CompletedTask;
        }

        [Fact]
        public async Task RegisterUserAsync_ShouldAddUser_WhenUserIsUnique()
        {
            // Arrange
            var user = new User { Username = "testuser", Password = "testpass", Email = "test@test.com" };

            // Act
            await _dao.RegisterUserAsync(user);

            // Assert
            var retrievedUser = await _dao.GetUserAsync("testuser");
            Assert.NotNull(retrievedUser);
            Assert.Equal("testuser", retrievedUser.Username);
        }

        [Fact]
        public async Task RegisterUserAsync_ShouldThrowException_WhenDuplicateUser()
        {
            // Arrange
            var user = new User { Username = "testuser", Password = "testpass", Email = "test@test.com" };
            await _dao.RegisterUserAsync(user);

            // Act & Assert
            async Task action() => await _dao.RegisterUserAsync(user);
            await Assert.ThrowsAsync<DuplicateNameException>(action);
        }

        [Fact]
        public async Task ValidateUserAsync_ShouldReturnUser_WhenCredentialsAreCorrect()
        {
            // Arrange
            var user = new User { Username = "testuser", Password = "testpass", Email = "test@test.com" };
            await _dao.RegisterUserAsync(user);

            // Act
            var validatedUser = await _dao.ValidateUserAsync("testuser", "testpass");

            // Assert
            Assert.NotNull(validatedUser);
            Assert.Equal("testuser", validatedUser.Username);
        }

        [Fact]
        public async Task ValidateUserAsync_ShouldThrow_WhenPasswordIsIncorrect()
        {
            var user = new User { Username = "testuser", Password = "testpass", Email = "test@test.com" };
            await _dao.RegisterUserAsync(user);

            // Act & Assert
            var exception = await Assert.ThrowsAsync<UnauthorizedAccessException>(() => _dao.ValidateUserAsync("testuser", "wrongpass"));
            Assert.Equal("Password is incorrect.", exception.Message);
        }

    }
}