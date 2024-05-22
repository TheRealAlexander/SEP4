import { useState, useEffect } from 'react';

const API_BASE_URL = "http://broker:5202";

const useTournamentData = (tournamentID) => {
  const [tournamentData, setTournamentData] = useState({
    id: tournamentID,
    rounds: [],
    scoreboard: []
  });
  const [currentRoundIndex, setCurrentRoundIndex] = useState(0);
  const [loading, setLoading] = useState(true);
  const [error, setError] = useState(null);

  useEffect(() => {
    const fetchTournamentData = async () => {
      try {
        // Use the provided dummy JSON
        const dummyData = {
          id: tournamentID,
          rounds: [
            {
              id: 1,
              courts: Array.from({ length: 16 }, (_, i) => ({
                id: i + 1,
                players: [
                  [{ id: i * 4 + 1, name: `Player ${i * 4 + 1}` }, { id: i * 4 + 2, name: `Player ${i * 4 + 2}` }],
                  [{ id: i * 4 + 3, name: `Player ${i * 4 + 3}` }, { id: i * 4 + 4, name: `Player ${i * 4 + 4}` }]
                ],
                score1: 0,
                score2: 0
              })),
            }
          ],
          scoreboard: Array.from({ length: 64 }, (_, i) => ({
            id: i + 1,
            name: `Player ${i + 1}`,
            score: Math.floor(Math.random() * 100)
          }))
        };

        // Simulate a delay to mimic an API call
        await new Promise(resolve => setTimeout(resolve, 1000));

        setTournamentData(dummyData);
        setLoading(false);
      } catch (err) {
        setError(err);
        setLoading(false);
      }
    };

    fetchTournamentData();
  }, [tournamentID]);

  const updateScores = (roundId, courtId, newScores) => {
    setTournamentData(prev => {
      const rounds = prev.rounds.map(round => {
        if (round.id === roundId) {
          const courts = round.courts.map(court => {
            if (court.id === courtId) {
              return { ...court, score1: newScores[0], score2: newScores[1] };
            }
            return court;
          });
          return { ...round, courts };
        }
        return round;
      });
      return { ...prev, rounds };
    });
  };

  const navigateRound = (direction) => {
    setCurrentRoundIndex(prev => {
      const newIndex = direction === 'next' ? prev + 1 : prev - 1;
      return Math.max(0, Math.min(newIndex, tournamentData.rounds.length - 1));
    });
  };

  return { tournamentData, currentRoundIndex, updateScores, navigateRound, loading, error };
};

export default useTournamentData;
