using System.ComponentModel.DataAnnotations;
using System.IdentityModel.Tokens.Jwt;
using System.Security.Claims;
using System.Text;
using Microsoft.AspNetCore.Mvc;
using Microsoft.IdentityModel.Tokens;

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
            var user = await authService.GetUser(username);
            if (user == null)
            {
                return NotFound("User not found.");
            }
            return Ok(user);
        }
        catch (Exception ex)
        {
            // Log the exception details here to troubleshoot in case of failures
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
            await authService.RegisterUser(userCreationDTO);
            // After registration, redirect to the GetUser endpoint to fetch and return the registered user details
            return CreatedAtAction(nameof(GetUser), new { username = userCreationDTO.Username }, userCreationDTO);
        }
        catch (ValidationException ex)
        {
            return BadRequest(ex.Message);
        }
        catch (Exception ex)
        {
            return StatusCode(StatusCodes.Status500InternalServerError, "Error while creating new user.");
            throw new Exception(ex.Message);
        }
    }


}