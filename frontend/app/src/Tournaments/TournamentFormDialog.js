import React, { useState } from 'react';
import { 
     Dialog, 
     DialogTitle, 
     DialogContent, 
     TextField, 
     Button, 
     Select, 
     MenuItem, 
     FormControl, 
     InputLabel, 
     DialogActions,
     Snackbar 
} from '../MUI_imports';
import TounamentService from '../Services/TournamentService';

export default function TournamentFormDialog({ open, onClose }) {
     const [nameOfTournament, setNameOfTournament] = useState('');
     const [dateAndTime, setDateAndTime] = useState('');
     const [description, setDescription] = useState('');
     const [baneAntal, setBaneAntal] = useState(1);
     const [format, setFormat] = useState('');
     const [snackbarOpen, setSnackbarOpen] = useState(false);
     const [snackbarMessage, setSnackbarMessage] = useState('');
 
     const handleCloseSnackbar = () => {
         setSnackbarOpen(false);
     };
 
     async function handleSubmit() {
        if (!nameOfTournament || !dateAndTime || !description || !format) {
            setSnackbarMessage("All fields must be filled!");
            setSnackbarOpen(true);
            return;
        }

        if (new Date(dateAndTime) < new Date()) {
            setSnackbarMessage("The entered date is in the past!");
            setSnackbarOpen(true);
            return;
        }

        const tournamentData = {
            Name: nameOfTournament,
            DateAndTime: dateAndTime,
            Description: description,
            FieldCount: baneAntal,
            Format: format,
            Participants: [],
            State: 1,
            tournamentID: null // This should be assigned by the backend
        };
        // Handle send data to backend here
        try {
            const response = await TounamentService.CreateTournament(tournamentData);

            if (response.status === 200) {
                setSnackbarMessage("Tournament created successfully!");
                setSnackbarOpen(true);
                onClose(); // Close the dialog after submitting
            } else {
                setSnackbarMessage("Error creating tournament! - " + response.status);
                setSnackbarOpen(true);
            }
        }
        catch (error) {
            setSnackbarMessage("Error creating tournament! - " + error);
            setSnackbarOpen(true);
        }
    }
 
     return (
         <Dialog open={open} onClose={onClose}>
             <DialogTitle>Create New Tournament</DialogTitle>
             <DialogContent>
                 <TextField
                     autoFocus
                     margin="dense"
                     id="name"
                     label="Tournament Name"
                     type="text"
                     fullWidth
                     variant="standard"
                     value={nameOfTournament}
                     onChange={(e) => setNameOfTournament(e.target.value)}
                 />
                 <TextField
                     margin="dense"
                     id="datetime"
                     label="Date and Time"
                     type="datetime-local"
                     fullWidth
                     variant="standard"
                     InputLabelProps={{
                         shrink: true,
                     }}
                     value={dateAndTime}
                     onChange={(e) => setDateAndTime(e.target.value)}
                 />
                 <TextField
                     margin="dense"
                     id="description"
                     label="Description"
                     type="text"
                     fullWidth
                     variant="standard"
                     value={description}
                     onChange={(e) => setDescription(e.target.value)}
                 />
                 <FormControl fullWidth margin="dense">
                     <InputLabel id="baneAntal-label">Bane Antal</InputLabel>
                     <Select
                         labelId="baneAntal-label"
                         id="baneAntal"
                         value={baneAntal}
                         label="Bane Antal"
                         onChange={(e) => setBaneAntal(e.target.value)}
                     >
                         {[...Array(16).keys()].map(num => (
                             <MenuItem key={num + 1} value={num + 1}>{num + 1}</MenuItem>
                         ))}
                     </Select>
                 </FormControl>
                 <FormControl fullWidth margin="dense">
                     <InputLabel id="format-label">Format</InputLabel>
                     <Select
                         labelId="format-label"
                         id="format"
                         value={format}
                         label="Format"
                         onChange={(e) => setFormat(e.target.value)}
                     >
                         <MenuItem value="Americano">Americano</MenuItem>
                         <MenuItem value="Mexicano">Mexicano</MenuItem>
                     </Select>
                 </FormControl>
             </DialogContent>
             <DialogActions>
                 <Button onClick={onClose}>Close</Button>
                 <Button onClick={handleSubmit}>Create</Button>
             </DialogActions>
             <Snackbar // Snackbar(pop-up) for error messages
                 anchorOrigin={{ vertical: 'bottom', horizontal: 'center'}}
                 open={snackbarOpen}
                 autoHideDuration={6000}
                 onClose={handleCloseSnackbar}
                 message={snackbarMessage}
             />
         </Dialog>
     );
}
