import React from 'react';
import Box from '@mui/material/Box';
import Typography from '@mui/material/Typography';

export default function HomePage () {
  return (
    <Box 
    sx={{ 
        display: 'flex', 
        justifyContent: 'center', 
        alignItems: 'center', 
        height: '100vh', 
        padding: '2rem', 
        textAlign: 'center' 
      }}
    >
      <Typography variant="h4">
        This website is a school project and should not be taken seriously.
        This websites purpose is to show the skills of the students.

      </Typography>
    </Box>
  );
}

