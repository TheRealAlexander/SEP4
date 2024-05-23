import React from 'react';
import { Typography, Card, CardContent, Grid } from '@mui/material';

const TournamentDetails = ({ name, format, numberOfCourts, pointsPerMatch }) => {
  return (
    <Card variant="outlined" sx={{ minWidth: 275, margin: '16px auto', maxWidth: 1200 }}>
      <CardContent>
        <Grid container spacing={1} justifyContent="center" alignItems="center" textAlign="center">
          <Grid item xs={12}>
            <Typography variant="h4" component="div" gutterBottom>
              {name}
            </Typography>
          </Grid>
          <Grid item xs={12}>
            <Typography variant="h6" component="div" gutterBottom>
              Format: {format}
            </Typography>
          </Grid>
          <Grid item xs={12}>
            <Typography variant="h6" component="div" gutterBottom>
              Number of Courts: {numberOfCourts}
            </Typography>
          </Grid>
          <Grid item xs={12}>
            <Typography variant="body1" component="div">
              Points Per Match: {pointsPerMatch}
            </Typography>
          </Grid>
        </Grid>
      </CardContent>
    </Card>
  );
};

export default TournamentDetails;
