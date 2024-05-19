import React, { useState, useEffect } from 'react';
import TournamentRound from './TournamentRound';
import { Paper, Typography, Box, Button, Grid } from '@mui/material';
import ArrowBackIosIcon from '@mui/icons-material/ArrowBackIos';
import ArrowForwardIosIcon from '@mui/icons-material/ArrowForwardIos';
import Scoreboard from './Scoreboard';
import useNextRound from '../Hooks/Tournament/useNextRound';

const TournamentLiveOverview = ({ tournamentID }) => {
    const { nextRound, scores, loading, error } = useNextRound(tournamentID);
    const [currentRound, setCurrentRound] = useState(0);
    const [dialogOpen, setDialogOpen] = useState({});
    const [tournamentData, setTournamentData] = useState(null);

    useEffect(() => {
        if (nextRound) {
            setTournamentData(nextRound);
        }
    }, [nextRound]);

    const handleNavigation = (direction) => {
        setCurrentRound(prevRound => {
            const nextRound = direction === 'next' ? prevRound + 1 : prevRound - 1;
            return Math.max(0, Math.min(nextRound, tournamentData?.rounds.length - 1));
        });
    };

    const handleUpdate = (courtId, newScores) => {
        const updatedCourts = tournamentData.rounds[currentRound].courts.map(court => {
            if (court.id === courtId) {
                return {
                    ...court,
                    score1: newScores[0],
                    score2: newScores[1]
                };
            }
            return court;
        });
        const updatedRounds = tournamentData.rounds.map((round, index) => {
            if (index === currentRound) {
                return { ...round, courts: updatedCourts };
            }
            return round;
        });
        setTournamentData({ ...tournamentData, rounds: updatedRounds });
    };

    const handleClick = (courtId) => {
        setDialogOpen(prevState => ({ ...prevState, [courtId]: true }));
        console.log('open ' + courtId);
    };

    const handleClose = (courtId) => {
        setDialogOpen(prevState => ({ ...prevState, [courtId]: false }));
        console.log('close ' + courtId);
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
                            disabled={currentRound === 0}
                            startIcon={<ArrowBackIosIcon />}
                        />
                        <Typography variant="h6" sx={{ mx: 2 }}>
                            Round {tournamentData.rounds[currentRound].id}
                        </Typography>
                        <Button
                            variant="contained"
                            onClick={() => handleNavigation('next')}
                            disabled={currentRound === tournamentData.rounds.length - 1}
                            endIcon={<ArrowForwardIosIcon />}
                        />
                    </Box>
                    <TournamentRound
                        courts={tournamentData.rounds[currentRound].courts}
                        onUpdate={handleUpdate}
                        dialogOpen={dialogOpen}
                        handleClick={handleClick}
                        handleClose={handleClose}
                    />
                </Paper>
            </Grid>
            <Grid item xs={12} md={4}>
                <Scoreboard scores={scores} />
            </Grid>
        </Grid>
    );
};

export default TournamentLiveOverview;
