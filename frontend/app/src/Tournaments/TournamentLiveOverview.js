import React, { useState } from 'react';
import TournamentRound from './TournamentRound';
import { Paper, Typography, Box, Button, Grid } from '@mui/material';
import ArrowBackIosIcon from '@mui/icons-material/ArrowBackIos';
import ArrowForwardIosIcon from '@mui/icons-material/ArrowForwardIos';
import Scoreboard from './Scoreboard';
import useTournamentData from '../Hooks/Tournament/useTournamentData'; // Import the new hook

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
        navigateRound(direction); // Simplify navigation handling
    };

    const handleUpdate = (courtId, newScores) => {
        // Simplify score updates
        updateScores(tournamentData.rounds[currentRoundIndex].id, courtId, newScores);
    };

    const handleClick = (courtId) => {
        setDialogOpen(prevState => ({ ...prevState, [courtId]: true }));
    };

    const handleClose = (courtId) => {
        setDialogOpen(prevState => ({ ...prevState, [courtId]: false }));
    };

    if (loading) {
        return <Typography>Loading...</Typography>;
    }

    if (error) {
        return <Typography>Error: {error.message}</Typography>;
    }

    if (!tournamentData || !tournamentData.rounds || tournamentData.rounds.length === 0) {
        return <Typography>No data available</Typography>;
    }

    return (
        <Grid container spacing={2} sx={{ margin: 'auto', maxWidth: 1400 }}>
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
                            Round {tournamentData.rounds[currentRoundIndex].id}
                        </Typography>
                        <Button
                            variant="contained"
                            onClick={() => handleNavigation('next')}
                            disabled={currentRoundIndex === tournamentData.rounds.length - 1}
                            endIcon={<ArrowForwardIosIcon />}
                        />
                    </Box>
                    <TournamentRound
                        courts={tournamentData.rounds[currentRoundIndex].courts}
                        onUpdate={handleUpdate}
                        dialogOpen={dialogOpen}
                        handleClick={handleClick}
                        handleClose={handleClose}
                    />
                </Paper>
            </Grid>
            <Grid item xs={12} md={4}>
                <Scoreboard scores={tournamentData.scoreboard} />
            </Grid>
        </Grid>
    );
};

export default TournamentLiveOverview;
