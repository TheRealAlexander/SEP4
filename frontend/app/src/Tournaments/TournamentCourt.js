import React, { useState, useEffect } from "react";
import {
  Card as MuiCard,
  CardContent,
  Typography,
  Dialog,
  DialogActions,
  DialogContent,
  DialogContentText,
  TextField,
  Box,
  Button,
} from "@mui/material";

const CourtScore = ({ children }) => (
  <Box
    sx={{
      display: "flex",
      alignItems: "center",
      justifyContent: "center",
      fontSize: "1.5rem",
      fontWeight: "bold",
      margin: 1,
    }}
  >{children}</Box>
);

const TeamColumn = ({ team }) => (
  <Box
    sx={{
      display: "flex",
      flexDirection: "column",
      alignItems: "center",
      justifyContent: "center",
      margin: 1,
      width: "100px",
    }}
  >
    {team.map(player => (
      <Typography key={player.id} variant="body1" fontWeight="bold">
        {player.name}
      </Typography>
    ))}
  </Box>
);

const TournamentCourt = ({
  court,
  onUpdate,
  open,
  handleClose,
  handleClick,
}) => {
  const [tempScore, setTempScore] = useState([0, 0]);

  useEffect(() => {
    setTempScore([
      court.score1,
      court.score2
    ]);
  }, [court.score1, court.score2]);

  const handleUpdate = () => {
    onUpdate(court.id, tempScore);
    handleClose();
  };

  const handleScoreChange = (index, value) => {
    const newScores = [...tempScore];
    newScores[index] = value === '' ? '' : Number(value);
    setTempScore(newScores);
  };

  // Check for incomplete data structure
  if (!court || !court.players || court.players[0].length < 2 || court.players[1].length < 2) {
    return <div>Loading or incomplete data...</div>;
  }

  return (
    <MuiCard
      variant="outlined"
      onClick={handleClick}
      sx={{
        width: "100%",
        transition: "transform 0.2s, box-shadow 0.2s",
        "&:hover": {
          transform: "scale(1.05)",
          boxShadow: "0px 10px 15px rgba(0,0,0,0.3)",
        },
      }}
    >
      <CardContent sx={{ textAlign: "center" }}>
        <Box sx={{ display: "flex", justifyContent: "space-between", alignItems: "center" }}>
          <TeamColumn team={court.players[0]} />
          <Typography variant="h6">vs</Typography>
          <TeamColumn team={court.players[1]} />
        </Box>
        <CourtScore>{tempScore[0]} - {tempScore[1]}</CourtScore>
      </CardContent>
      <Dialog open={open} onClose={handleClose}>
        <DialogContent>
          <DialogContentText>Set the new scores for each team.</DialogContentText>
          <TextField
            autoFocus
            margin="dense"
            id="score1"
            label="Team 1 Score"
            type="number"
            fullWidth
            variant="outlined"
            value={tempScore[0]}
            onChange={(e) => handleScoreChange(0, e.target.value)}
          />
          <TextField
            margin="dense"
            id="score2"
            label="Team 2 Score"
            type="number"
            fullWidth
            variant="outlined"
            value={tempScore[1]}
            onChange={(e) => handleScoreChange(1, e.target.value)}
          />
        </DialogContent>
        <DialogActions>
          <Button onClick={handleClose}>Cancel</Button>
          <Button onClick={handleUpdate}>Update</Button>
        </DialogActions>
      </Dialog>
    </MuiCard>
  );
};

export default TournamentCourt;
