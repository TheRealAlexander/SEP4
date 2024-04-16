using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Mvc;

[ApiController]
[Route("[controller]")]
[Authorize]
public class TestController : ControllerBase
{
    
[HttpGet("authorized")]
public ActionResult GetAsAuthorized()
{
    return Ok("This was accepted as authorized");
}

[HttpGet("/test/admin"), Authorize("MustBeAdmin")]
    public ActionResult GetAsAdmin()
    {
        return Ok("This was accepted as admin role");
    }

}