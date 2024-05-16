import React from "react";
import {
  Card,
  CardActionArea,
  CardContent,
  Typography,
  Grid,
} from "../MUI_imports";

function TournamentItem({ tournament, onClick }) {
  return (
    <Grid item xs={12} sm={6}>
      <Card
        sx={{
          margin: 10,
          marginTop: 6,
          display: "flex",
          flexDirection: "column",
          alignItems: "center",
          justifyContent: "center",
        }}
      >
        <CardActionArea onClick={() => onClick(tournament)}>
          <CardContent
            sx={{
              padding: 10,
              display: "flex",
              flexDirection: "column",
              alignItems: "center",
              justifyContent: "center",
            }}
          >
            <Typography
              gutterBottom
              variant="h5"
              component="div"
              sx={{
                fontSize: { xs: "1.2rem", sm: "1.5rem" },
              }}
            >
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
    </Grid>
  );
}

export default TournamentItem;
