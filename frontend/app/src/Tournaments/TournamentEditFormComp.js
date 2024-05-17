import React, { useState } from 'react';
import { 
     Dialog, 
     DialogTitle, 
     DialogContent, 
     TextField, 
     Button, 
     DialogActions, 
     Select, 
     MenuItem, 
     FormControl, 
     InputLabel, 
     IconButton, 
     Tooltip 
} from '../MUI_imports';
import DeleteIcon from '@mui/icons-material/Delete'; // MUI delete icon

export default function TournamentEditForm({ open, onClose, onSave, onDelete, tournament }) {
    const [name, setName] = useState(tournament.name);
    const [date, setDate] = useState(tournament.date);
    const [description, setDescription] = useState(tournament.description);
    const [format, setFormat] = useState(tournament.format);
    const [baneAntal, setBaneAntal] = useState(tournament.baneAntal);

    const handleSave = () => {
        const updatedTournament = {
            id: tournament.id,
            name,
            date,
            description,
            format,
            baneAntal
        };
        onSave(updatedTournament);
        onClose();
    };

    const confirmAndDelete = () => {
        if (window.confirm("Are you sure you want to delete this tournament?")) {
            onDelete(tournament.id);
            onClose();
        }
    };

    return (
        <Dialog open={open} onClose={onClose} aria-labelledby="edit-tournament-dialog-title">
            <DialogTitle id="edit-tournament-dialog-title">Edit Tournament</DialogTitle>
            <DialogContent>
                <TextField
                    label="Tournament Name"
                    value={name}
                    onChange={(e) => setName(e.target.value)}
                    fullWidth
                    margin="dense"
                />
                <TextField
                    label="Date"
                    type="datetime-local"
                    InputLabelProps={{
                        shrink: true,
                    }}
                    value={date}
                    onChange={(e) => setDate(e.target.value)}
                    fullWidth
                    margin="dense"
                />
                <TextField
                    label="Event Description"
                    value={description}
                    onChange={(e) => setDescription(e.target.value)}
                    fullWidth
                    margin="dense"
                />
                <FormControl fullWidth margin="dense">
                    <InputLabel id="format-label">Format</InputLabel>
                    <Select
                        labelId="format-label"
                        id="format"
                        value={format}
                        onChange={(e) => setFormat(e.target.value)}
                    >
                        <MenuItem value="Americano">Americano</MenuItem>
                        <MenuItem value="Mexicano">Mexicano</MenuItem>
                    </Select>
                </FormControl>
                <FormControl fullWidth margin="dense">
                    <InputLabel id="baneAntal-label">Game Fields</InputLabel>
                    <Select
                        labelId="baneAntal-label"
                        id="baneAntal"
                        value={baneAntal}
                        onChange={(e) => setBaneAntal(e.target.value)}
                    >
                        {[...Array(16).keys()].map(num => (
                            <MenuItem key={num + 1} value={num + 1}>{num + 1}</MenuItem>
                        ))}
                    </Select>
                </FormControl>
            </DialogContent>
            <DialogActions>
                <Tooltip title="Delete Tournament">
                    <IconButton onClick={confirmAndDelete} color="error">
                        <DeleteIcon />
                    </IconButton>
                </Tooltip>
                <Button onClick={onClose}>Cancel</Button>
                <Button onClick={handleSave}>Save Changes</Button>
            </DialogActions>
        </Dialog>
    );
}
