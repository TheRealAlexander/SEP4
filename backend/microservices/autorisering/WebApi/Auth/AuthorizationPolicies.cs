using System.Security.Claims;

public static class AuthorizationPolicies {
     public static void AddPolicies(IServiceCollection services)
    {
        services.AddAuthorizationCore(options =>
        {
            options.AddPolicy("MustBeAdmin", a =>
                a.RequireAuthenticatedUser().RequireClaim(ClaimTypes.Role, "Admin"));
            options.AddPolicy("MustBeUser", a =>
                a.RequireAuthenticatedUser().RequireClaim(ClaimTypes.Role, "User"));
            options.AddPolicy("MustBeSuperUser",
                a => a.RequireAuthenticatedUser().RequireClaim(ClaimTypes.Role, "SuperUser"));
        });
    }
}