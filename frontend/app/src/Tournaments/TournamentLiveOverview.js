import React, { useState, useEffect } from 'react';
import TournamentRound from './TournamentRound';
import { Paper, Typography, Box, Button, Grid } from '@mui/material';
import ArrowBackIosIcon from '@mui/icons-material/ArrowBackIos';
import ArrowForwardIosIcon from '@mui/icons-material/ArrowForwardIos';
import Scoreboard from './Scoreboard';
import useNextRound from '../Hooks/Tournament/useNextRound';

const TournamentLiveOverview = ({ tournamentID }) => {
    const { nextRound, loading, error } = useNextRound(tournamentID);
    const [currentRound, setCurrentRound] = useState(0);
    const [dialogOpen, setDialogOpen] = useState({});

    const [tournamentData, setTournamentData] = useState(null);

    // Update tournamentData when nextRound changes
    useEffect(() => {
        if (nextRound) {
            setTournamentData(nextRound);
        }
    }, [nextRound]);

    const handleNavigation = (direction) => {
        setCurrentRound(prevRound => {
            const nextRound = direction === 'next' ? prevRound + 1 : prevRound - 1;
            return Math.max(0, Math.min(nextRound, tournamentData.rounds.length - 1));
        });
    };

    const handleUpdate = (matchId, newScores) => {
        const updatedRounds = tournamentData.rounds.map(round => {
            return {
                ...round,
                matches: round.matches.map(match => {
                    if (match.id === matchId) {
                        return { ...match, score1: newScores[0], score2: newScores[1] };
                    }
                    return match;
                })
            };
        });
        setTournamentData({ rounds: updatedRounds });
    };

    const handleClick = (matchId) => {
        setDialogOpen(prevState => ({ ...prevState, [matchId]: true }));
        console.log('open ' + matchId);
    };

    const handleClose = (matchId) => {
        setDialogOpen(prevState => ({ ...prevState, [matchId]: false }));
        console.log('close ' + matchId);
    };

    if (loading) {
        return <Typography>Loading...</Typography>;
    }

    if (error) {
        return <Typography>Error: {error.message}</Typography>;
    }

    if (!tournamentData) {
        return null;
    }

    return (
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
            <Grid container spacing={2}>
                <Grid item xs={12} md={4} sx={{ padding: 2 }}>
                    <TournamentRound
                        round={tournamentData.rounds[currentRound]}
                        onUpdate={handleUpdate}
                        dialogOpen={dialogOpen}
                        handleClick={handleClick}
                        handleClose={handleClose}
                    />
                </Grid>

                <Grid item xs={12} md={4} sx={{ padding: 2 }}>
                    <Scoreboard />
                </Grid>
            </Grid>
        </Paper>
    );
};

export default TournamentLiveOverview;
