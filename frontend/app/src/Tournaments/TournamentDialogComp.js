import React, { useState } from "react";

import {
  Dialog,
  DialogTitle,
  DialogContent,
  DialogActions,
  TextField,
  Button,
  Typography,
  Box,
} from "../MUI_imports";

function TournamentDialog({ open, onClose, tournament }) {
  const [participantName, setParticipantName] = useState("");

  const handleRegister = () => {
    // Handle registering for tournament
    // Add participantName to tournament.participants
    // Update tournament.currentParticipants
    console.log("Registering:", participantName);
    setParticipantName(""); // Reset input after registering
    //onClose();
  };

  const handleStartEvent = () => {
    // Handle redirect to event page
    // Redirect to event page with tournament data
    console.log("Starting event:", tournament.name);
    onClose();
  };

  return (
    <Dialog
      open={open}
      onClose={onClose}
      aria-labelledby="tournament-dialog-title"
      fullWidth
      maxWidth="sm"
    >
      <DialogTitle id="tournament-dialog-title">
        <Box display="flex" justifyContent="space-between" alignItems="center">
          {tournament.name}
          <Button
            color="primary"
            variant="contained"
            onClick={() => handleStartEvent()}
          >
            Start Event
          </Button>
        </Box>
      </DialogTitle>
      <DialogContent>
        <Typography>Date: {tournament.date}</Typography>
        <Typography>
          Current Participants: {tournament.currentParticipants}
        </Typography>
        <Typography>Event Description: {tournament.description}</Typography>
        <Typography>Participants:</Typography>
        <Box
          sx={{
            display: "grid",
            gridTemplateColumns: "repeat(3, 1fr)",
            gap: 1,
            marginBottom: 2,
          }}
        >
          {tournament.participants.map((participant, index) => (
            <Box
              key={index}
              sx={{ padding: 1, border: "1px solid #ccc", borderRadius: "4px" }}
            >
              {participant}
            </Box>
          ))}
        </Box>
        <TextField
          label="Your Name"
          value={participantName}
          onChange={(e) => setParticipantName(e.target.value)}
          fullWidth
        />
      </DialogContent>
      <DialogActions>
        <Button onClick={handleRegister}>Register</Button>
      </DialogActions>
    </Dialog>
  );
}

export default TournamentDialog;
