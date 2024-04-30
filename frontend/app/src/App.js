import './App.css';
import { BrowserRouter as Router, Route, Routes, Navigate, } from 'react-router-dom';
import ThermostatData from './Components/Thermostat/ThermostatData';
import ClimatePage from './Components/ClimatePage/ClimatePage';
import HumidityComponent from './Components/Humidity/HumidityData';
import Controls from "./Components/Controls/Controls";
import { useNavigate } from "react-router-dom";
import Login from './Components/Login/Login';
import { useLocation } from 'react-router-dom';
import Registration from './Components/Registration/Registration';


import * as React from 'react';
import AppBar from '@mui/material/AppBar';
import Box from '@mui/material/Box';
import Toolbar from '@mui/material/Toolbar';
import IconButton from '@mui/material/IconButton';
import Typography from '@mui/material/Typography';
import Menu from '@mui/material/Menu';
import MenuIcon from '@mui/icons-material/Menu';
import Container from '@mui/material/Container';
import Avatar from '@mui/material/Avatar';
import Button from '@mui/material/Button';
import Tooltip from '@mui/material/Tooltip';
import MenuItem from '@mui/material/MenuItem';
import AdbIcon from '@mui/icons-material/Adb';

const pages = ["Home", "Controls", "Data"];
const settings = ["Profile", "Account", "Dashboard", "Logout"];

function App() {
  return (
    <Box sx={{ display: "flex", flexDirection: "column", height: "100%" }}>
      <Router>
        <AppContent />
      </Router>
    </Box>
  );
}

function AppContent() {
  const location = useLocation();

  return (
    <>
         {(location.pathname !== '/login' && location.pathname !== '/registration') && <ResponsiveAppBar />}

      <Box component="main" sx={{
        flexGrow: 1,
        p: 3,
        display: "flex",
        flexDirection: 'column',
        alignItems: 'center',
        justifyContent: 'center',
        height: '100vh',
        mt: '-5vh',
        width: (location.pathname === '/login' || location.pathname === '/registration') ? '100%' : `calc(100% - 240px)` }}>
        <Toolbar />

        <div className="App">
          <Routes>
            <Route path="/" element={<ClimatePage data={data} />} />
            <Route path="/thermostat" element={<ThermostatData />} />
            <Route path="/humidity" element={<HumidityComponent />} />
            <Route path="/Controls/1" element={<Controls />} />
            <Route path="/login" element={<Login />} /> 
            <Route path="/registration" element={<Registration />} /> 
          </Routes>
        </div>
      </Box>
    </>
  );
}

function ResponsiveAppBar() {
  const [anchorElNav, setAnchorElNav] = React.useState(null);
  const [anchorElUser, setAnchorElUser] = React.useState(null);
  const navigate = useNavigate();

  const pathMapping = {
    Home: "/",
    Controls: "/Controls/1",
  };

  const handleOpenNavMenu = (event) => {
    setAnchorElNav(event.currentTarget);
  };
  const handleOpenUserMenu = (event) => {
    setAnchorElUser(event.currentTarget);
  };

  const handleCloseNavMenu = () => {
    setAnchorElNav(null);
  };

  const handleCloseUserMenu = () => {
    setAnchorElUser(null);
  };

  const handleNavigate = (buttonText) => {
    const path = pathMapping[buttonText];
    if (path) {
      navigate(path);
    } else {
      console.error("No path found for button text: ", buttonText);
    }
  };

  return (
    <AppBar position="static" style={{ zIndex: 1100 }}>
      {" "}
      <Container maxWidth="xl">
        <Toolbar disableGutters>
          <Typography
            variant="h6"
            noWrap
            component="a"
            href="#app-bar-with-responsive-menu"
            sx={{
              mr: 2,
              display: { xs: "none", md: "flex" },
              fontFamily: "monospace",
              fontWeight: 700,
              letterSpacing: ".3rem",
              color: "inherit",
              textDecoration: "none",
            }}
          >
            LOGO
          </Typography>

          <Box sx={{ flexGrow: 1, display: { xs: "flex", md: "none" } }}>
            <IconButton
              size="large"
              aria-label="account of current user"
              aria-controls="menu-appbar"
              aria-haspopup="true"
              onClick={handleOpenNavMenu}
              color="inherit"
            >
              <MenuIcon />
            </IconButton>
            <Menu
              id="menu-appbar"
              anchorEl={anchorElNav}
              anchorOrigin={{
                vertical: "bottom",
                horizontal: "left",
              }}
              keepMounted
              transformOrigin={{
                vertical: "top",
                horizontal: "left",
              }}
              open={Boolean(anchorElNav)}
              onClose={handleCloseNavMenu}
              sx={{
                display: { xs: "block", md: "none" },
              }}
            >
              {pages.map((page) => (
                <MenuItem key={page} onClick={() => handleNavigate(page)}>
                  <Typography textAlign="center">{page}</Typography>
                </MenuItem>
              ))}
            </Menu>
          </Box>

          <Box sx={{ flexGrow: 1, display: { xs: "none", md: "flex" } }}>
            {pages.map((page) => (
              <Button
                key={page}
                onClick={() => {
                  // Here we change to also handle navigation
                  handleCloseNavMenu();
                  handleNavigate(page);
                }}
                sx={{ my: 2, color: "white", display: "block" }}
              >
                {page}
              </Button>
            ))}
          </Box>

          <Box sx={{ flexGrow: 0 }}>
            <Tooltip title="Open settings">
              <IconButton onClick={handleOpenUserMenu} sx={{ p: 0 }}>
                <Avatar alt="Remy Sharp" src="/static/images/avatar/2.jpg" />
              </IconButton>
            </Tooltip>
            <Menu
              sx={{ mt: "45px" }}
              id="menu-appbar"
              anchorEl={anchorElUser}
              anchorOrigin={{
                vertical: "top",
                horizontal: "right",
              }}
              keepMounted
              transformOrigin={{
                vertical: "top",
                horizontal: "right",
              }}
              open={Boolean(anchorElUser)}
              onClose={handleCloseUserMenu}
            >
              {settings.map((setting) => (
                <MenuItem key={setting} onClick={handleCloseUserMenu}>
                  <Typography textAlign="center">{setting}</Typography>
                </MenuItem>
              ))}
            </Menu>
          </Box>
        </Toolbar>
      </Container>
    </AppBar>
  );
}

let data = {
  time: "12:00",
  location: "Living Room",
  temperature: 19,
  humidity: 50,
  co2_concentration: 800,
};

export default App;
export { ResponsiveAppBar };
