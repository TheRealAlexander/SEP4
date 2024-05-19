import React from 'react';
import TournamentCourt from './TournamentCourt';
import { Box, Typography, Grid } from '@mui/material';

const TournamentRound = ({ courts, onUpdate, dialogOpen, handleClick, handleClose }) => {
    return (
        <Box sx={{ margin: 2 }}>
            <Typography variant="h5" gutterBottom component="div" sx={{ textAlign: 'center' }}>
                Courts
            </Typography>
            <Grid container spacing={2}>
                {courts.map(court => (
                    <Grid item xs={12} sm={6} md={3} key={court.id}>
                        <TournamentCourt
                            court={court}
                            onUpdate={onUpdate}
                            open={dialogOpen[court.id] || false}
                            handleClose={() => handleClose(court.id)}
                            handleClick={() => handleClick(court.id)}
                        />
                    </Grid>
                ))}
            </Grid>
        </Box>
    );
};

export default TournamentRound;
