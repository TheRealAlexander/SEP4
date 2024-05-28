import React from 'react';
import { Card, CardContent, Typography, Button } from '@mui/material';

const TournamentCard = ({ tournament, onCardClick }) => {
  if (!tournament) {
    return null;
  }


  return (
    <Card
      onClick={() => onCardClick(tournament.Id)}
      sx={{
        cursor: 'pointer',
        minWidth: '400px',
        transition: 'transform 0.3s, box-shadow 0.3s',
        '&:hover': {
          transform: 'scale(1.05)',
          boxShadow: '0 4px 20px rgba(0, 0, 0, 0.2)',
        },
      }}
    >
      <CardContent>
        <Typography gutterBottom variant="h5" component="div">
          {tournament.Name}
        </Typography>
        <Typography variant="body2" color="text.secondary">
          Format: {tournament.Format}
        </Typography>
        <Typography variant="body2" color="text.secondary">
          Points per Match: {tournament.PointsPerMatch}
        </Typography>
        <Typography variant="body2" color="text.secondary">
          Number of Courts: {tournament.NumberOfCourts}
        </Typography>
        <Typography variant="body2" color="text.secondary">
          Number of Players: {tournament.Players.length}
        </Typography>
        <Typography variant="body2" color="text.secondary">
          Date: {new Date(tournament.Date).toLocaleDateString()}
        </Typography>
      </CardContent>
    </Card>
  );
};

export default TournamentCard;
