import Sidebar from "../Sidebar/Sidebar";
import React from 'react';
import Box from '@mui/material/Box';
import Toolbar from '@mui/material/Toolbar';
import { Typography } from "@mui/material";


export default function Controls() { 
    return (
        <Box sx={{ display: 'flex' }}>
        <Sidebar />
        <Box component="main" sx={{ flexGrow: 1, p: 3 }}>
          <Toolbar /> 
          <Typography paragraph>
            
          </Typography>
        </Box>
      </Box>
    );
  }