import { useNavigate } from 'react-router-dom';
import React, { useState } from "react";
import EditIcon from "@mui/icons-material/Edit"; // MUI Edit Icon
import TournamentEditForm from "./TournamentEditFormComp";
import { AddParticipant, RemoveTournament, UpdateTournament } from "../Services/TournamentService";
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
  Snackbar,
  Alert,
} from "../MUI_imports";

export default function TournamentDialog({ open, onClose, tournament }) {
  const [participantName, setParticipantName] = useState("");
  const [editOpen, setEditOpen] = useState(false);
  const [snackbarOpen, setSnackbarOpen] = useState(false);
  const [snackbarMessage, setSnackbarMessage] = useState('');
  const [snackbarSeverity, setSnackbarSeverity] = useState('success');

  const navigate = useNavigate();

  const handleSnackbarClose = () => {
    setSnackbarOpen(false);
  };

  const handleRegister = async () => {
    try {
      const response = AddParticipant(tournament.id, participantName);

      if (response.status === 200) {
        setSnackbarMessage("Participant added successfully!");
        setSnackbarSeverity('success');
        setSnackbarOpen(true);
      }
      else {
        setSnackbarMessage("Failed to add participant. Status code: " + response.status);
        setSnackbarSeverity('error');
        setSnackbarOpen(true);
      }
    } catch (error) {
      setSnackbarMessage("Failed to add participant. Error: " + error);
      setSnackbarSeverity('error');
      setSnackbarOpen(true);
    }
  };
  
  const handleStartEvent = () => { 
     // Handle redirect to event page
     // Redirect to event page with tournament data
     console.log("Starting event:", tournament.name);
     navigate('/TournamentLiveOverview', { state: { tournament } });
     onClose();
  }

  const handleDeleteTournament = async (tournamentID) => {
    try {
      const response = await RemoveTournament(tournamentID);

      if (response.status === 200) {
        setSnackbarMessage("Tournament deleted successfully!");
        setSnackbarSeverity('success');
        setSnackbarOpen(true);
        onClose();
      }
      else {
        setSnackbarMessage("Failed to delete tournament. Status code: " + response.status);
        setSnackbarSeverity('error');
        setSnackbarOpen(true);
      }
    } catch (error) {
      setSnackbarMessage("Failed to delete tournament. Error: " + error);
      setSnackbarSeverity('error');
      setSnackbarOpen(true);
    }
  };

  const handleSaveEdits = async (updatedTournament) => {
    try {
      const response = await UpdateTournament(updatedTournament);

      if (response.status === 200) {
        setSnackbarMessage("Tournament updated successfully!");
        setSnackbarSeverity('success');
        setSnackbarOpen(true);
        onClose();
      }
      else {
        setSnackbarMessage("Failed to update tournament. Status code: " + response.status);
        setSnackbarSeverity('error');
        setSnackbarOpen(true);
      }
    } catch (error) {
      setSnackbarMessage("Failed to update tournament. Error: " + error);
      setSnackbarSeverity('error');
      setSnackbarOpen(true);
    }
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
          <Button color="primary" variant="contained" onClick={handleStartEvent}>
            Start Event
          </Button>
        </Box>
      </DialogTitle>
      <DialogContent>
        <Typography>Date: {tournament.DateAndTime}</Typography>
        <Typography>
          Current Participants: {tournament.Participants}
        </Typography>
        <Typography>Event Description: {tournament.Description}</Typography>
        <Typography>Format: {tournament.Format}</Typography>
        <Typography>Game Fields: {tournament.FieldCount}</Typography>
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
      <Snackbar open={snackbarOpen} autoHideDuration={6000} onClose={handleSnackbarClose}>
        <Alert onClose={handleSnackbarClose} severity={snackbarSeverity} sx={{ width: '100%' }}>
          {snackbarMessage}
        </Alert>
      </Snackbar>
    </Dialog>
  );
}