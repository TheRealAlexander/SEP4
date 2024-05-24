using WebApi.DAO;
using WebApi.Services;
using SharedObjects.Auth;

var builder = WebApplication.CreateBuilder(args);

// Add services to the container.
builder.Services.AddControllers().AddNewtonsoftJson(options =>
{
    options.SerializerSettings.ReferenceLoopHandling = Newtonsoft.Json.ReferenceLoopHandling.Ignore;
});
// Learn more about configuring Swagger/OpenAPI at https://aka.ms/aspnetcore/swashbuckle
builder.Services.AddEndpointsApiExplorer();
builder.Services.AddSwaggerGen();

// Register the MongoDbContext
builder.Services.AddSingleton<MongoDbContext>(sp =>
    new MongoDbContext(
        builder.Configuration.GetConnectionString("MongoDb"),
        "indeklima_db"
    )
);
builder.Services.AddScoped<ISensorDataService, SensorDataService>();
builder.Services.AddScoped<ISensorDataDAO, SensorDataDAO>();
builder.Services.AddScoped<ISensorGoalService, SensorGoalService>();
builder.Services.AddScoped<ISensorGoalDAO, SensorGoalDAO>();
builder.Services.AddScoped<IIOTControlService, IOTControlService>();

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

app.UseAuthorization();

app.MapControllers();

app.Run();