import React, { useState } from "react";
import {
  Card,
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
import { styled } from "@mui/system";

const MatchScore = styled(Box)(({ theme }) => ({
  display: "flex",
  alignItems: "center",
  justifyContent: "center",
  fontSize: "1.5rem",
  fontWeight: "bold",
  margin: theme.spacing(1),
}));

const TournamentMatch = ({
  match,
  onUpdate,
  open,
  handleClose,
  handleClick,
}) => {
  const [tempScore, setTempScore] = useState([match.score1, match.score2]);

  const handleUpdate = () => {
    onUpdate(match.id, tempScore);
    handleClose();
  };

  const handleScoreChange = (index, value) => {
    const newScores = [...tempScore];
    newScores[index] = value === '' ? '' : Number(value);
    setTempScore(newScores);
  };

  return (
    <Card variant="outlined" sx={{ width: "100%" }} onClick={handleClick}>
      <CardContent sx={{ textAlign: "center" }}>
        <Typography variant="h6">
          {match.team1} vs {match.team2}
        </Typography>
        <MatchScore>
          {match.score1} - {match.score2}
        </MatchScore>
      </CardContent>

      <Dialog open={open} onClose={handleClose}>
        <DialogContent>
          <DialogContentText>
            Set the new scores for each team.
          </DialogContentText>
          <TextField
            autoFocus
            margin="dense"
            id="score1"
            label={match.team1}
            type="number"
            fullWidth
            variant="outlined"
            value={tempScore[0]}
            onChange={(e) => handleScoreChange(0, e.target.value)}
          />
          <TextField
            margin="dense"
            id="score2"
            label={match.team2}
            type="number"
            fullWidth
            variant="outlined"
            value={tempScore[1]}
            onChange={(e) => handleScoreChange(1, e.target.value)}
          />
        </DialogContent>
        <DialogActions>
          <Button
            onClick={(e) => {
              e.stopPropagation();
              handleClose();
            }}
          >
            Cancel
          </Button>
          <Button
            onClick={(e) => {
              e.stopPropagation();
              handleUpdate();
            }}
          >
            Update
          </Button>
        </DialogActions>
      </Dialog>
    </Card>
  );
};

export default TournamentMatch;
