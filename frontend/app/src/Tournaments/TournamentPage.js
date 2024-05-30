import React, { useState } from "react";

import TournamentItem from "./TournamentItemComp";
import TournamentDialog from "./TournamentDialogComp";
import TournamentFormDialog from "./TournamentFormDialog";
import { isAuthenticated } from "../RouteProtection/PrivateRoute";

import { Button } from "../MUI_imports";
import { GetAllTournaments } from "../Services/TournamentService";

export default function TournamentPage() {
  const [open, setOpen] = useState(false);
  const [selectedTournament, setSelectedTournament] = useState(null);
  const [formOpen, setFormOpen] = useState(false);

  let tournaments = GetAllTournaments();

  const handleTournamentClick = (tournament) => {
    setSelectedTournament(tournament);
    setOpen(true);
  };

  const handleClose = () => {
    setOpen(false);
  };

  return (
    <div>
      <Button
        variant="contained"
        color="primary"
        onClick={() => setFormOpen(true)}
        disabled={!isAuthenticated()}
      >
        Create New Tournament
      </Button>
      {formOpen && (
        <TournamentFormDialog
          open={formOpen}
          onClose={() => setFormOpen(false)}
        />
      )}
      <div>
        {Array.isArray(tournaments) &&
          tournaments.map((tournament) => (
            <TournamentItem
              key={tournament.TournamentID}
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
      </div>
    </div>
  );
}
