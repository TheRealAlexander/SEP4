import React, { useState } from 'react';

import { 
     Dialog, 
     DialogTitle, 
     DialogContent, 
     DialogActions, 
     TextField, 
     Button, 
     Typography, 
     List, 
     ListItem 
} from '../MUI_imports';


function TournamentDialog({ open, onClose, tournament }) {
  const [participantName, setParticipantName] = useState('');

  const handleRegister = () => {
    console.log("Registering:", participantName);
    setParticipantName('');  // Reset input after registering
    onClose();  // Close dialog after registering
  };

  return (
    <Dialog open={open} onClose={onClose} aria-labelledby="tournament-dialog-title">
      <DialogTitle id="tournament-dialog-title">{tournament.name}</DialogTitle>
      <DialogContent>
        <Typography>Date: {tournament.date}</Typography>
        <Typography>Current Participants: {tournament.currentParticipants}</Typography>
        <Typography>Event Description: {tournament.description}</Typography>
        <List>
          {tournament.participants.map((participant, index) => (
            <ListItem key={index}>{participant}</ListItem>
          ))}
        </List>
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
