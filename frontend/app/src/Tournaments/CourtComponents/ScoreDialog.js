import React, { useState, useEffect } from "react";
import {
  Dialog,
  DialogActions,
  DialogContent,
  DialogContentText,
  TextField,
  Box,
  Button,
  Typography,
  Divider,
} from "@mui/material";

const ScoreDialog = ({
  open,
  handleClose,
  handleUpdate,
  pointsPerMatch,
  court,
  tempScore,
  setTempScore,
  errors,
  setErrors,
  index,
}) => {
  const [team1Players, setTeam1Players] = useState("");
  const [team2Players, setTeam2Players] = useState("");

  useEffect(() => {
    if (court && court.teams && court.teams.length >= 2) {
      setTeam1Players(
        court.teams[0].map((player) => player?.Name || "Unknown Player").join(" & ")
      );
      setTeam2Players(
        court.teams[1].map((player) => player?.Name || "Unknown Player").join(" & ")
      );
    }
  }, [court]);

  const handleScoreChange = (index, value) => {
    const newScores = [...tempScore];
    const score = value === "" ? "" : Number(value);
    newScores[index] = score;
    setTempScore(newScores);
    validateScores(newScores);
  };

  const validateScores = (scores) => {
    const newErrors = [null, null];
    let valid = true;

    scores.forEach((score, index) => {
      if (score < 0) {
        newErrors[index] = "Score cannot be less than 0";
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

  return (
    <Dialog open={open} onClose={handleClose}>
      <DialogContent>
        <Box component="span" sx={{ display: "inline" }}>
          <Typography variant="h6" component="span">
            {" "}
            Court #{index + 1}:{" "}
          </Typography>
          <Typography variant="subtitle1" component="span">
            {" "}
            {team1Players}{" "}
          </Typography>
          <Typography variant="h6" component="span" sx={{ textDecoration: "bold" }}>
            {" "}
            -vs-{" "}
          </Typography>
          <Typography variant="subtitle1" component="span">
            {" "}
            {team2Players}{" "}
          </Typography>
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
        <Button
          onClick={(e) => {
            e.stopPropagation(); // Stop the event from propagating to the parent card
            handleClose();
          }}
        >
          Cancel
        </Button>
        <Button
          onClick={(e) => {
            e.stopPropagation(); // Stop the event from propagating to the parent card
            handleUpdate();
          }}
          disabled={errors[0] !== null || errors[1] !== null}
        >
          Update
        </Button>
      </DialogActions>
    </Dialog>
  );
};

export default ScoreDialog;
