import React from 'react';
import TournamentMatch from './TournamentMatch';
import { Box, Typography } from '@mui/material';

const TournamentRound = ({ round, onUpdate, dialogOpen, handleClick, handleClose }) => {
    return (
        <Box sx={{ margin: 2 }}>
            <Typography variant="h5" gutterBottom component="div" sx={{ textAlign: 'center' }}>
                Round {round.id}
            </Typography>
            <Box sx={{ display: 'flex', flexDirection: 'column', alignItems: 'center', gap: 2 }}>
                {round.matches.map(match => (
                    <TournamentMatch
                        key={match.id}
                        match={match}
                        onUpdate={onUpdate}
                        open={dialogOpen[match.id] || false}
                        handleClose={() => handleClose(match.id)}
                        handleClick={() => handleClick(match.id)}
                    />
                ))}
            </Box>
        </Box>
    );
};

export default TournamentRound;
