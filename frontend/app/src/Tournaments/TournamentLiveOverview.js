import React, { useState } from 'react';
import TournamentRound from './TournamentRound';
import { Paper, Typography, Box, Button, Grid } from '@mui/material';
import ArrowBackIosIcon from '@mui/icons-material/ArrowBackIos';
import ArrowForwardIosIcon from '@mui/icons-material/ArrowForwardIos';
import Scoreboard from './Scoreboard';
import useTournamentData from '../Hooks/Tournament/useTournamentData';
import TournamentDetails from './TournamentDetails';

const TournamentLiveOverview = ({ tournamentID }) => {
  const {
    tournamentData,
    currentRoundIndex,
    updateScores,
    navigateRound,
    loading,
    error
  } = useTournamentData(tournamentID);

  const [dialogOpen, setDialogOpen] = useState({});

  const handleNavigation = (direction) => {
    navigateRound(direction);
  };

  const handleUpdate = (courtId, newScores) => {
    updateScores(tournamentData.Rounds[currentRoundIndex].RoundNumber, courtId, newScores);
  };
  
  

  const handleClick = (courtIndex) => {
    setDialogOpen(prevState => ({ ...prevState, [courtIndex]: true }));
  };

  const handleClose = (courtIndex) => {
    setDialogOpen(prevState => ({ ...prevState, [courtIndex]: false }));
  };

  if (loading) {
    return <Typography>Loading...</Typography>;
  }

  if (error) {
    return <Typography>Error: {error.message}</Typography>;
  }

  if (!tournamentData || !tournamentData.Rounds || tournamentData.Rounds.length === 0) {
    return <Typography>No data available</Typography>;
  }

  return (
    <Grid container spacing={2} sx={{ margin: 'auto', maxWidth: 1400 }}>
      <Grid item xs={12}>
        <TournamentDetails 
          name={tournamentData.Name} 
          format={tournamentData.Format} 
          numberOfCourts={tournamentData.NumberOfCourts} 
          pointsPerMatch={tournamentData.PointsPerMatch} 
        />
      </Grid>
      <Grid item xs={12} md={8}>
        <Paper elevation={3} sx={{ p: 3, margin: 'auto', maxWidth: 1200 }}>
          <Box sx={{ display: 'flex', justifyContent: 'center', alignItems: 'center', marginBottom: 2 }}>
            <Button
              variant="contained"
              onClick={() => handleNavigation('previous')}
              disabled={currentRoundIndex === 0}
              startIcon={<ArrowBackIosIcon />}
            />
            <Typography variant="h6" sx={{ mx: 2 }}>
              Round {tournamentData.Rounds[currentRoundIndex].RoundNumber}
            </Typography>
            <Button
              variant="contained"
              onClick={() => handleNavigation('next')}
              disabled={currentRoundIndex === tournamentData.Rounds.length - 1}
              endIcon={<ArrowForwardIosIcon />}
            />
          </Box>
          <TournamentRound
            courts={tournamentData.Rounds[currentRoundIndex].Courts}
            onUpdate={handleUpdate}
            dialogOpen={dialogOpen}
            handleClick={handleClick}
            handleClose={handleClose}
          />
        </Paper>
      </Grid>
      <Grid item xs={12} md={4}>
        <Scoreboard scores={tournamentData.Players} />
      </Grid>
    </Grid>
  );
};

export default TournamentLiveOverview;
