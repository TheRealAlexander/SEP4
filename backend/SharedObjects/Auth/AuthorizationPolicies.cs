using System.Text;
using System.Security.Claims;
using Microsoft.AspNetCore.Authentication.JwtBearer;
using Microsoft.IdentityModel.Tokens;

namespace SharedObjects.Auth;

public static class AuthorizationPolicies
{
    public static void AddAuth(WebApplicationBuilder builder)
    {
        AuthorizationPolicies.AddPolicies(builder.Services);

        builder.Services.AddAuthentication(JwtBearerDefaults.AuthenticationScheme).AddJwtBearer(options =>
        {
            options.RequireHttpsMetadata = false;
            options.SaveToken = true;
            options.TokenValidationParameters = new TokenValidationParameters()
            {
                ValidateIssuer = true,
                ValidateAudience = true,
                ValidAudience = builder.Configuration["Jwt:Audience"],
                ValidIssuer = builder.Configuration["Jwt:Issuer"],
                IssuerSigningKey = new SymmetricSecurityKey(Encoding.UTF8.GetBytes(builder.Configuration["Jwt:Key"]))
            };
        });
    }

    public static void AddPolicies(IServiceCollection services)
    {
        services.AddAuthorizationCore(options =>
        {
            options.AddPolicy("MustBeAdmin",
                a => a.RequireAuthenticatedUser().RequireClaim(ClaimTypes.Role, "Admin"));
            options.AddPolicy("MustBeUser",
                a => a.RequireAuthenticatedUser().RequireClaim(ClaimTypes.Role, "User"));
            options.AddPolicy("MustBeSuperUser",
                a => a.RequireAuthenticatedUser().RequireClaim(ClaimTypes.Role, "SuperUser"));
        });
    }
}
