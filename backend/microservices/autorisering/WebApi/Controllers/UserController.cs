using System.ComponentModel.DataAnnotations;
using Microsoft.AspNetCore.Authorization;
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
    private readonly IUserService _userService;

    public UserController(IConfiguration config, IUserService userService)
    {
        this.config = config;
        this._userService = userService;
    }
    
    [HttpGet("{username}")]
    [Authorize(Policy = "MustBeAdmin")]
    public async Task<ActionResult<User>> GetUserAsync(string username)
    {
        try
        {
            var user = await _userService.GetUserAsync(username);
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
    [Authorize(Policy = "MustBeAdmin")]
    public async Task<ActionResult<List<User>>> GetAllUsersAsync()
    {
        try
        {
            var users = await _userService.GetAllUsersAsync();
            return Ok(users);
        }
        catch (Exception ex)
        {
            Console.WriteLine($"An error occurred: {ex.ToString()}");  // Log full exception stack trace
            return StatusCode(StatusCodes.Status500InternalServerError, "Error retrieving data from the database.");
        }
    }
    
    [HttpPost("register")]
    public async Task<ActionResult<User>> RegisterUserAsync([FromBody] UserCreationDTO userCreationDTO)
    {
        if (!ModelState.IsValid)
        {
            return BadRequest(ModelState);
        }

        try
        {
            await _userService.RegisterUserAsync(userCreationDTO);
            return Ok();
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
            return BadRequest(new { error = "Something went wrong." });
        }
    }

    [HttpPost("swapRoles")]
    [Authorize(Policy = "MustBeAdmin")]
    public async Task<ActionResult<List<User>>> SwapRolesAsync([FromBody] List<User> users)
    {
        if (users.IsNullOrEmpty())
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
                else if (user.Role == "User")
                {
                    user.Role = "SuperUser";
                }
                else
                {
                    return BadRequest("Role must be either User or SuperUser!");
                }
                
                await _userService.UpdateUserAsync(user);

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