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
        const generateDummyData = (tournamentID) => {
            const playerCount = 64;
            const courtCount = 16;
            const roundCount = 3;
            
            // Generate 64 unique players
            const players = Array.from({ length: playerCount }, (_, i) => ({
              id: i + 1,
              name: `Player ${i + 1}`
            }));
          
            const rounds = Array.from({ length: roundCount }, (_, roundIndex) => ({
              id: roundIndex + 1,
              courts: []
            }));
          
            // Distribute players to courts for each round
            for (let roundIndex = 0; roundIndex < roundCount; roundIndex++) {
              let shuffledPlayers = [...players];
              
              // Shuffle players to ensure different team compositions per round
              // Fisher-Yates (Durstenfeld) shuffle algorithm
              for (let i = shuffledPlayers.length - 1; i > 0; i--) {
                const j = Math.floor(Math.random() * (i + 1));
                [shuffledPlayers[i], shuffledPlayers[j]] = [shuffledPlayers[j], shuffledPlayers[i]];
              }
          
              // Assign players to courts
              const courts = Array.from({ length: courtCount }, (_, courtIndex) => {
                const baseIndex = courtIndex * 4;
                return {
                  id: courtIndex + 1,
                  players: [
                    [shuffledPlayers[baseIndex], shuffledPlayers[baseIndex + 1]],
                    [shuffledPlayers[baseIndex + 2], shuffledPlayers[baseIndex + 3]]
                  ],
                  score1: 0,
                  score2: 0
                };
              });
          
              rounds[roundIndex].courts = courts;
            }
          
            const scoreboard = players.map(player => ({
              id: player.id,
              name: player.name,
              score: Math.floor(Math.random() * 100)
            }));
          
            return {
              id: tournamentID,
              rounds,
              scoreboard
            };
          };

        const dummyData = generateDummyData(tournamentID);
          
          
          

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
      }).sort((a, b) => b.score - a.score);  // Sort the scoreboard by score, descending
  
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
