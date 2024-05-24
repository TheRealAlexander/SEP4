using System.Text;
using Microsoft.AspNetCore.Authentication.JwtBearer;
using Microsoft.IdentityModel.Tokens;
using WebApi.DAO;
using WebApi.Services;
using SharedObjects.Auth;

var builder = WebApplication.CreateBuilder(args);

// Add services to the container.
// Learn more about configuring Swagger/OpenAPI at https://aka.ms/aspnetcore/swashbuckle
builder.Services.AddControllers();
builder.Services.AddEndpointsApiExplorer();
builder.Services.AddSwaggerGen();

// Register the MongoDbContext
builder.Services.AddSingleton<MongoDbContext>(sp =>
    new MongoDbContext(
        builder.Configuration.GetConnectionString("MongoDB"),
        "auth_db"
    )
);
builder.Services.AddScoped<IUserDAO, UserDAO>();
builder.Services.AddScoped<IUserService, UserService>();

AuthorizationPolicies.AddAuth(builder);

var app = builder.Build();

// Configure the HTTP request pipeline.
if (app.Environment.IsDevelopment())
{
    app.UseSwagger();
    app.UseSwaggerUI();
}

app.UseCors(x => x
    .AllowAnyMethod()
    .AllowAnyHeader()
    .SetIsOriginAllowed(origin => true) // allow any origin
    .AllowCredentials());

app.UseHttpsRedirection();

app.UseAuthentication();

app.UseAuthorization();

app.MapControllers();

app.Run();
