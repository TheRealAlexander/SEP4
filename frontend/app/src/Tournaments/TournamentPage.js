import React, { useState } from "react";

import TournamentItem from "./TournamentItemComp";
import TournamentDialog from "./TournamentDialogComp";
import { Box } from "../MUI_imports";

export default function TournamentPage() {
  const [open, setOpen] = useState(false);
  const [selectedTournament, setSelectedTournament] = useState(null);

  //Dummy data for tournaments
  const Participants = [
    "Alice",
    "Bob",
    "Charlie",
    "Dave",
    "Eve",
    "Frank",
    "Grace",
    "Heidi",
    "Ivan",
    "Judy",
    "Kevin",
    "Linda",
    "Mallory",
    "Nia",
    "Oscar",
    "Peggy",
    "Quinn",
    "Rene",
    "Sue",
    "Trent",
    "Ursula",
    "Victor",
    "Wendy",
    "Xander",
    "Yvonne",
    "Zane",
  ];
  const tournaments = [
    {
      id: 1,
      name: "Tournament A",
      date: "2024-06-01",
      currentParticipants: Participants.length,
      description: "This is a sample tournament A.",
      participants: Participants,
    },
    {
      id: 2,
      name: "Tournament B",
      date: "2024-07-15",
      currentParticipants: 8,
      description: "This is a sample tournament B.",
      participants: ["Charlie", "Dave"],
    },
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
    <Box
      p={2}
      sx={{
        display: "flex",
        flexDirection: "row",
        alignItems: "center",
        justifyContent: "center",
      }}
    >
      {tournaments.map((tournament) => (
        <TournamentItem
          key={tournament.id}
          tournament={tournament}
          onClick={handleTournamentClick}
        />
      ))}
      {selectedTournament && (
        <TournamentDialog
          open={open}
          onClose={handleClose}
          tournament={selectedTournament}
        />
      )}
    </Box>
  );
}
