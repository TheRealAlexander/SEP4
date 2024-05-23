import React from 'react';
import { useNavigate } from 'react-router-dom';
import { Grid, Typography } from '@mui/material';
import TournamentCard from './OngoindTournamentComponents/TournamentCard';
import useDummyTournaments from '../Hooks/Tournament/useDummyTournaments';

const OngoingTournamentPage = () => {
  const { tournaments, loading, error } = useDummyTournaments();
  const navigate = useNavigate();

  const handleCardClick = (tournamentID) => {
    navigate(`/tournament/${tournamentID}`);
  };

  if (loading) {
    return <Typography>Loading...</Typography>;
  }

  if (error) {
    return <Typography>Error: {error.message}</Typography>;
  }

  return (
    <Grid container spacing={3} direction="column" sx={{ padding: 4 }}>
      {tournaments.map((tournament) => (
        <Grid item key={tournament.Id} xs={12} sm={6} md={4}>
          <TournamentCard tournament={tournament} onCardClick={handleCardClick} />
        </Grid>
      ))}
    </Grid>
  );
};

export default OngoingTournamentPage;
