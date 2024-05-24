import axios from 'axios';
import { useState, useEffect } from 'react';

const API_BASE_URL = 'http://broker:5202'; // Ensure this is the correct base URL for your API

const useTournamentData = (tournamentID) => {
  const [tournamentData, setTournamentData] = useState(null);
  const [currentRoundIndex, setCurrentRoundIndex] = useState(0);
  const [loading, setLoading] = useState(true);
  const [error, setError] = useState(null);

  useEffect(() => {
    const fetchTournamentData = async () => {
      try {
        const response = await axios.get(`${API_BASE_URL}/broker/tournaments/${tournamentID}`);
        setTournamentData(response.data);
        setLoading(false);
      } catch (err) {
        setError(err);
        setLoading(false);
      }
    };

    fetchTournamentData();
  }, [tournamentID]);

  const parseCourtIndex = (courtIndex) => {
    const parts = courtIndex.split('-');
    return { roundIndex: parseInt(parts[1], 10), courtIndex: parseInt(parts[2], 10) };
  };

  const updateScores = (roundNumber, courtId, newScores) => {
    const { roundIndex, courtIndex } = parseCourtIndex(courtId);

    setTournamentData(prev => {
      let newPlayers = [...prev.Players];
      const newRounds = prev.Rounds.map((round, rIndex) => {
        if (rIndex === roundIndex) {
          const newCourts = round.Courts.map((court, cIndex) => {
            if (cIndex === courtIndex) {
              const oldScores = court.scores;
              const scoreDifferences = newScores.map((score, index) => score - oldScores[index]);

              court.teams.forEach((team, teamIndex) => {
                team.forEach(player => {
                  const playerIndex = newPlayers.findIndex(p => p.Name === player.Name);
                  if (playerIndex !== -1) {
                    newPlayers[playerIndex].Points += scoreDifferences[teamIndex];
                  }
                });
              });

              return { ...court, scores: newScores, previousScores: oldScores };
            }
            return court;
          });
          return { ...round, Courts: newCourts };
        }
        return round;
      });
      return { ...prev, Rounds: newRounds, Players: newPlayers };
    });
  };

  const navigateRound = (direction) => {
    setCurrentRoundIndex(prev => {
      const newIndex = direction === 'next' ? prev + 1 : prev - 1;
      return Math.max(0, Math.min(newIndex, tournamentData.Rounds.length - 1));
    });
  };

  return { tournamentData, currentRoundIndex, updateScores, navigateRound, loading, error };
};

export default useTournamentData;
