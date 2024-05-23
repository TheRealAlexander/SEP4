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
  Divider,
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
  >
    {children}
  </Box>
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
    {team && team.map((player, index) => (
      <Typography key={index} variant="body1" fontWeight="bold">
        {player?.Name || 'Unknown Player'}
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
  pointsPerMatch,
  index,
}) => {
  const [tempScore, setTempScore] = useState([0, 0]);
  const [errors, setErrors] = useState([null, null]);

  useEffect(() => {
    setTempScore(court.scores || [0, 0]);
  }, [court.scores]);

  const handleUpdate = () => {
    if (validateScores(tempScore)) {
      onUpdate(court.id, tempScore);
      handleClose();
    }
  };

  const handleScoreChange = (index, value) => {
    const newScores = [...tempScore];
    const score = value === '' ? '' : Number(value);
    newScores[index] = score;
    setTempScore(newScores);
    validateScores(newScores);
  };

  const validateScores = (scores) => {
    const newErrors = [null, null];
    let valid = true;

    scores.forEach((score, index) => {
      if (score < 0) {
        newErrors[index] = 'Score cannot be less than 0';
        valid = false;
      } else if (score > pointsPerMatch) {
        newErrors[index] = `Score cannot be greater than ${pointsPerMatch}`;
        valid = false;
      } else if (scores[0] + scores[1] > pointsPerMatch) {
        newErrors[index] = `Total score cannot exceed ${pointsPerMatch}`;
        valid = false;
      }
    });

    setErrors(newErrors);
    return valid;
  };

  if (!court || !court.teams || court.teams.length < 2 || !court.teams[0] || !court.teams[1]) {
    return <div>Loading or incomplete data...</div>;
  }

  const team1Players = court.teams[0].map(player => player?.Name || 'Unknown Player').join(' & ');
  const team2Players = court.teams[1].map(player => player?.Name || 'Unknown Player').join(' & ');


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
        <Typography variant="h6" gutterBottom> Court #{index+1} </Typography>
        <Divider />
        <Box sx={{ display: "flex", justifyContent: "space-between", alignItems: "center" }}>
          <TeamColumn team={court.teams[0]} />
          <Typography variant="h6">vs</Typography>
          <TeamColumn team={court.teams[1]} />
        </Box>
        <CourtScore>{tempScore[0]} - {tempScore[1]}</CourtScore>
      </CardContent>
      <Dialog open={open} onClose={handleClose}>
        <DialogContent>
          <Box component="span" sx={{ display: "inline" }}>
            <Typography variant="h6" component="span"> Court #{index + 1}: </Typography>
            <Typography variant="subtitle1" component="span"> {team1Players} </Typography>
            <Typography variant="h6" component="span" sx={{textDecoration: "bold"}}> -vs- </Typography>
            <Typography variant="subtitle1" component="span"> {team2Players} </Typography>
          </Box>
          <Divider />
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
            error={!!errors[0]}
            helperText={errors[0]}
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
            error={!!errors[1]}
            helperText={errors[1]}
          />
        </DialogContent>
        <DialogActions>
          <Button onClick={(e) => {
            e.stopPropagation(); // Stop the event from propagating to the parent card
            handleClose();
          }}>Cancel</Button>
          <Button onClick={(e) => {
            e.stopPropagation(); // Stop the event from propagating to the parent card
            handleUpdate();
          }} disabled={errors[0] !== null || errors[1] !== null}>Update</Button>
        </DialogActions>
      </Dialog>
    </MuiCard>
  );
};

export default TournamentCourt;
