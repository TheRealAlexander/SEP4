import React, { useState } from "react";
import EditIcon from "@mui/icons-material/Edit"; // MUI Edit Icon
import TournamentEditForm from "./TournamentEditFormComp";
import {
  Dialog,
  DialogTitle,
  DialogContent,
  DialogActions,
  TextField,
  Button,
  Typography,
  Box,
  IconButton,
  Tooltip,
} from "../MUI_imports";

export default function TournamentDialog({ open, onClose, tournament }) {
  const [participantName, setParticipantName] = useState("");
  const [editOpen, setEditOpen] = useState(false);

  const handleRegister = () => {
    // Handle registering for tournament
    // Add participantName to tournament.participants
    // Update tournament.currentParticipants
    console.log("Registering:", participantName);
    setParticipantName(""); // Reset input after registering
  };

  const handleStartEvent = () => {
    // Handle redirect to event page
    // Request tournament data from the backend on new page
    console.log("Starting event:", tournament.name);
    onClose();
  };

  const handleDeleteTournament = (tournamentId) => {
    // Implement deletion logic.
    // Send a DELETE request to the backend to delete the tournament with id=tournament.id
    console.log("Deleting tournament:", tournament.id);
    onClose();
  };

  const handleSaveEdits = (updatedTournament) => {
    // Implement save edits logic.
    // Update the tournament data with the updatedTournament data.
    console.log("Saving edits:", updatedTournament);
    // Send updated tournament data to the backend
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
          <Box display="flex" alignItems="center">
            <Typography variant="h6" component="span" paddingRight={2}>
              {tournament.name}
            </Typography>
            <Tooltip title="Edit Tournament">
              <IconButton onClick={() => setEditOpen(true)} size="small">
                <EditIcon />
              </IconButton>
            </Tooltip>
          </Box>
          <Button
            color="primary"
            variant="contained"
            onClick={handleStartEvent}
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
        <Typography>Format: {tournament.format}</Typography>
        <Typography>Game Fields: {tournament.baneAntal}</Typography>
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
      <TournamentEditForm
        open={editOpen}
        onClose={() => setEditOpen(false)}
        onSave={handleSaveEdits}
        onDelete={handleDeleteTournament}
        tournament={tournament}
      />
    </Dialog>
  );
}