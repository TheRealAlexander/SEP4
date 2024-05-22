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
              // Generate rounds and courts
              ...Array.from({ length: 3 }, (_, roundIndex) => ({
                id: roundIndex + 1,
                courts: Array.from({ length: 16 }, (_, courtIndex) => {
                  const baseId = roundIndex * 64 + courtIndex * 4 + 1;  // Adjust baseId calculation for each round
                  return {
                    id: courtIndex + 1,
                    players: [
                      [{ id: baseId, name: `Player ${baseId}` }, { id: baseId + 1, name: `Player ${baseId + 1}` }],
                      [{ id: baseId + 2, name: `Player ${baseId + 2}` }, { id: baseId + 3, name: `Player ${baseId + 3}` }]
                    ],
                    score1: 0,
                    score2: 0
                  };
                }),
              })),
            ],
            scoreboard: Array.from({ length: 192 }, (_, i) => ({
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
      let scoreDifferences = [0, 0]; // To track score differences
  
      // Update the rounds and courts, and determine score differences
      const newRounds = prev.rounds.map(round => {
        if (round.id === roundId) {
          const newCourts = round.courts.map(court => {
            if (court.id === courtId) {
              // Calculate score differences
              scoreDifferences = [
                newScores[0] - court.score1,
                newScores[1] - court.score2
              ];
              return { ...court, score1: newScores[0], score2: newScores[1] };
            }
            return court;
          });
          return { ...round, courts: newCourts };
        }
        return round;
      });
  
      // Update the scoreboard based on the score differences
      const newScoreboard = prev.scoreboard.map(player => {
        const court = prev.rounds.find(round => round.id === roundId)
                        .courts.find(court => court.id === courtId);
  
        // Check if this player is in the updated court
        const playerIndexInCourt = court.players.flat().findIndex(p => p.id === player.id);
  
        // Determine which score difference to apply based on player's team
        if (playerIndexInCourt !== -1) {
          const teamIndex = Math.floor(playerIndexInCourt / 2); // Assuming 2 players per team
          return { ...player, score: player.score + scoreDifferences[teamIndex] };
        }
  
        return player;
      });
  
      return { ...prev, rounds: newRounds, scoreboard: newScoreboard };
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
