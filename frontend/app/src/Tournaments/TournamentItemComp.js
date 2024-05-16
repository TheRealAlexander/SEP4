import React from "react";

import { Card, CardActionArea, CardContent, Typography } from "../MUI_imports";

function TournamentItem({ tournament, onClick }) {
  return (
    <Card sx={{ margin: 0, marginTop: 6 }}>
      <CardActionArea onClick={() => onClick(tournament)}>
        <CardContent
          sx={{
            padding: 10,
            width: 250,
            display: "flex",
            flexDirection: "column",
            alignItems: "center",
            justifyContent: "center",
          }}
        >
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
