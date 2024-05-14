import React from 'react';

import { Card, CardActionArea, CardContent, Typography } from '../MUI_imports';

function TournamentItem({ tournament, onClick }) {
  return (
    <Card sx={{ Width: '100%', m: 2 }}>
      <CardActionArea onClick={() => onClick(tournament)}>
        <CardContent>
          <Typography gutterBottom variant="h5" component="div">
            {tournament.name}
          </Typography>
          <Typography variant="body2" color="text.secondary">
            Date: {tournament.date}
          </Typography>
          <Typography variant="body2" color="text.secondary">
            Participants: {tournament.currentParticipants}
          </Typography>
        </CardContent>
      </CardActionArea>
    </Card>
  );
}

export default TournamentItem;
