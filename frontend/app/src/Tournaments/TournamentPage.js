import React, { useState} from 'react';

import TournamentItem from './TournamentItemComp';
import TournamentDialog from './TournamentDialogComp';
import TournamentFormDialog from './TournamentFormDialog';

import { Button } from '../MUI_imports';

export default function TournamentPage() {
     const [open, setOpen] = useState(false);
     const [selectedTournament, setSelectedTournament] = useState(null);
     const [formOpen, setFormOpen] = useState(false);

     //Dummy data for tournaments
     const Participants = ["Alice", "Bob", "Charlie", "Dave", "Eve", "Frank", "Grace", "Heidi", "Ivan", "Judy", "Kevin", "Linda", "Mallory", "Nia", "Oscar", "Peggy", "Quinn", "Rene", "Sue", "Trent", "Ursula", "Victor", "Wendy", "Xander", "Yvonne", "Zane"];
     const tournaments = [
       { 
          id: 1, 
          name: "Tournament A", 
          date: "2024-06-01", 
          currentParticipants: Participants.length, 
          description: "This is a sample tournament A.", 
          participants: Participants 
       },
       { id: 2, name: "Tournament B", date: "2024-07-15", currentParticipants: 8, description: "This is a sample tournament B.", participants: ["Charlie", "Dave"] },
     ];
     //End of dummy data for tournaments
   
     const handleTournamentClick = (tournament) => {
       setSelectedTournament(tournament);
       setOpen(true);
     };
   
     const handleClose = () => {
       setOpen(false);
     };
   
     return (
      <div>
          <Button variant="contained" color="primary" onClick={() => setFormOpen(true)}>Create New Tournament</Button>
          {formOpen && <TournamentFormDialog open={formOpen} onClose={() => setFormOpen(false)} />}
       <div>
         {tournaments.map(tournament => (
           <TournamentItem key={tournament.id} tournament={tournament} onClick={handleTournamentClick} />
         ))}
         {selectedTournament && (
           <TournamentDialog
             open={open}
             onClose={handleClose}
             tournament={selectedTournament}
           />
         )}
       </div>
      </div>
     );
}