using System.ComponentModel.DataAnnotations;
using System.IdentityModel.Tokens.Jwt;
using System.Security.Claims;
using System.Text;
using Microsoft.AspNetCore.Mvc;
using Microsoft.IdentityModel.Tokens;
using WebApi.Models;
using WebApi.Services;
using System.Data;

[ApiController]
[Route("[controller]")]
public class UserController : ControllerBase
{
    private readonly IConfiguration config;
    private readonly IAuthService authService;

    public UserController(IConfiguration config, IAuthService authService)
    {
        this.config = config;
        this.authService = authService;
    }
    
    [HttpGet("{username}")]
    public async Task<ActionResult<User>> GetUser(string username)
    {
        try
        {
            var user = await authService.GetUserAsync(username);
            return Ok(user);
        }
        catch (Exception ex)
        {
            if (ex.InnerException is KeyNotFoundException)
            {
                // Console.WriteLine($"KeyNotFoundException caught: {ex.InnerException.ToString()}");
                return NotFound(ex.InnerException.Message);
            }
            // Console.WriteLine($"An error occurred: {ex.ToString()}");  // Log full exception stack trace
            return StatusCode(StatusCodes.Status500InternalServerError, "Error retrieving data from the database.");
        }
    }
    
    [HttpGet("/GetAllUsers")]
    public async Task<ActionResult<List<User>>> GetAllUsers()
    {
        try
        {
            var users = await authService.GetAllUsersAsync();
            return Ok(users);
        }
        catch (Exception ex)
        {
            Console.WriteLine($"An error occurred: {ex.ToString()}");  // Log full exception stack trace
            return StatusCode(StatusCodes.Status500InternalServerError, "Error retrieving data from the database.");
        }
    }
    
    [HttpPost("register")]
    public async Task<ActionResult<User>> RegisterUser([FromBody] UserCreationDTO userCreationDTO)
    {
        if (!ModelState.IsValid)
        {
            return BadRequest(ModelState);
        }

        try
        {
            await authService.RegisterUserAsync(userCreationDTO);
            // After registration, redirect to the GetUser endpoint to fetch and return the registered user details
            return CreatedAtAction(nameof(GetUser), new { username = userCreationDTO.Username }, userCreationDTO);
        }
        catch (DuplicateNameException ex)
        {
            return BadRequest(ex.Message);
        }
        catch (ValidationException ex)
        {
            return BadRequest(ex.Message);
        }
        catch (Exception ex)
        {
            Console.WriteLine(ex.Message);
            return StatusCode(StatusCodes.Status500InternalServerError, "Error while creating new user.");
        }
    }

    [HttpPost("swapRoles")]
    public async Task<ActionResult<List<User>>> SwapRolesAsync([FromBody] List<User> users)
    {
        if (users == null)
        {
            return BadRequest("No users provided.");
        }

        try
        {
            var processedUsers = new List<User>();
            foreach (var user in users)
            {
                if (user.Role == "SuperUser")
                {
                    user.Role = "User";
                }
                else
                {
                    user.Role = "SuperUser";
                }
                
                await authService.UpdateUserAsync(user);

                processedUsers.Add(user);
            }

            return Ok(processedUsers);
        }
        catch (Exception ex)
        {
            return StatusCode(StatusCodes.Status500InternalServerError, $"Error processing users: {ex.Message}");
        }

    }
    
    
    
}