import React from 'react';
import { Dialog, DialogActions, DialogContent, DialogContentText, DialogTitle, Button } from '@mui/material';

const PromptDialog = ({ open, handleClose, handleSave, handleDiscard }) => {
  return (
    <Dialog open={open} onClose={handleClose}>
      <DialogTitle>Unsaved Changes</DialogTitle>
      <DialogContent>
        <DialogContentText>
          Do you want to save the changes you have made?
        </DialogContentText>
      </DialogContent>
      <DialogActions>
        <Button onClick={handleDiscard} color="primary">
          No
        </Button>
        <Button onClick={handleSave} color="primary" autoFocus>
          Yes
        </Button>
      </DialogActions>
    </Dialog>
  );
};

export default PromptDialog;
