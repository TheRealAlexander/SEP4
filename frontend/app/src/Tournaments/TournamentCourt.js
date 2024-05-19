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

const CourtScore = styled(Box)(({ theme }) => ({
  display: "flex",
  alignItems: "center",
  justifyContent: "center",
  fontSize: "1.5rem",
  fontWeight: "bold",
  margin: theme.spacing(1),
}));

const TeamColumn = styled(Box)(({ theme }) => ({
  display: "flex",
  flexDirection: "column",
  alignItems: "center",
  justifyContent: "center",
  margin: theme.spacing(1),
  width: "100px"
}));

const TournamentCourt = ({
  court,
  onUpdate,
  open,
  handleClose,
  handleClick,
}) => {
  const [tempScore, setTempScore] = useState([court.score1, court.score2]);

  const handleUpdate = () => {
    onUpdate(court.id, tempScore);
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
        <Box sx={{ display: "flex", justifyContent: "space-between", alignItems: "center" }}>
          <TeamColumn>
          <Typography variant="body1" fontWeight="bold">{court.players[0][0].name}</Typography>
            <Typography variant="body1" fontWeight="bold">&</Typography>
            <Typography variant="body1" fontWeight="bold">{court.players[0][1].name}</Typography>
          </TeamColumn>
          <Typography variant="h6">vs</Typography>
          <TeamColumn>
            <Typography variant="body1" fontWeight="bold">{court.players[1][0].name}</Typography>
            <Typography variant="body1" fontWeight="bold">&</Typography>
            <Typography variant="body1" fontWeight="bold">{court.players[1][1].name}</Typography>
          </TeamColumn>
        </Box>
        <CourtScore>
          {court.score1} - {court.score2}
        </CourtScore>
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
            label={`${court.players[0][0].name} & ${court.players[0][1].name}`}
            type="number"
            fullWidth
            variant="outlined"
            value={tempScore[0]}
            onChange={(e) => handleScoreChange(0, e.target.value)}
          />
          <TextField
            margin="dense"
            id="score2"
            label={`${court.players[1][0].name} & ${court.players[1][1].name}`}
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

export default TournamentCourt;
