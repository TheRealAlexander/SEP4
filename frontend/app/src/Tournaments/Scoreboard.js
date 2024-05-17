import React from 'react';
import { Paper, Typography, Box } from '@mui/material';

const Scoreboard = () => {
  const scores = [
    { name: 'Team 1', score: 32 },
    { name: 'Team 2', score: 28 }
    
  ];

  return (
    <Paper elevation={3} sx={{ padding: 2 }}>
      <Typography variant="h4" gutterBottom>
        Scoreboard
      </Typography>
      <Box>
        {scores.map(({ name, score }) => (
          <Typography key={name} variant="h6">
            {name}: {score}
          </Typography>
        ))}
      </Box>
    </Paper>
  );
};

export default Scoreboard;
