import React from 'react';

import { Card, CardActionArea, CardContent, Typography } from '../MUI_imports';

export default function TournamentItem({ tournament, onClick }) {
  return (
    <Card sx={{ width: '100%', m: 2 }}>
      <CardActionArea onClick={() => onClick(tournament)}>
        <CardContent>
          <Typography gutterBottom variant="h5" component="div">
            {tournament.Name}
          </Typography>
          <Typography variant="body2" color="text.secondary">
            Date: {tournament.TimeAndDate}
          </Typography>
          <Typography variant="body2" color="text.secondary">
            Format: {tournament.Format}
          </Typography>
          <Typography variant="body2" color="text.secondary">
            Game Fields: {tournament.FieldCount}
          </Typography>
          <Typography variant="body2" color="text.secondary">
            Participants: {tournament.Participants}
          </Typography>
        </CardContent>
      </CardActionArea>
    </Card>
  );
}
