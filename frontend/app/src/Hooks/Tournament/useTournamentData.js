import { useState, useEffect } from 'react';

const useTournamentData = (tournamentID) => {
  const [tournamentData, setTournamentData] = useState({
    Id: tournamentID,
    Name: "Tournament Name",
    Format: "Mexicano",
    NumberOfCourts: 4,
    PointsPerMatch: 32,
    Players: [],
    State: 2,
    Rounds: [],
    NextRoundNumber: 1,
    SkippedARound: [],
    SkippedLastRound: []
  });
  const [currentRoundIndex, setCurrentRoundIndex] = useState(0);
  const [loading, setLoading] = useState(true);
  const [error, setError] = useState(null);

  useEffect(() => {
    const fetchTournamentData = async () => {
      try {
        const generateDummyData = (tournamentID) => {
          const playerCount = 16;
          const courtCount = 4;
          const roundCount = 3;

          const players = Array.from({ length: playerCount }, (_, i) => ({
            Name: `Player ${i + 1}`,
            Wins: 0,
            Draws: 0,
            Losses: 0,
            Points: 0
          }));

          const rounds = Array.from({ length: roundCount }, (_, roundIndex) => ({
            RoundNumber: roundIndex + 1,
            Courts: []
          }));

          for (let roundIndex = 0; roundIndex < roundCount; roundIndex++) {
            let shuffledPlayers = [...players];

            for (let i = shuffledPlayers.length - 1; i > 0; i--) {
              const j = Math.floor(Math.random() * (i + 1));
              [shuffledPlayers[i], shuffledPlayers[j]] = [shuffledPlayers[j], shuffledPlayers[i]];
            }

            const courts = Array.from({ length: courtCount }, (_, courtIndex) => {
              const baseIndex = courtIndex * 4;
              return {
                id: `court-${roundIndex}-${courtIndex}`,
                teams: [
                  [shuffledPlayers[baseIndex], shuffledPlayers[baseIndex + 1]],
                  [shuffledPlayers[baseIndex + 2], shuffledPlayers[baseIndex + 3]]
                ],
                scores: [0, 0], // Initial scores are set to 0
                previousScores: [0, 0] // Add a field to track previous scores
              };
            });

            rounds[roundIndex].Courts = courts;
          }

          return {
            Id: tournamentID,
            Name: "Tournament Name",
            Format: "Mexicano",
            NumberOfCourts: 4,
            PointsPerMatch: 32,
            Players: players,
            State: 2,
            Rounds: rounds,
            NextRoundNumber: 2,
            SkippedARound: [],
            SkippedLastRound: []
          };
        };

        const dummyData = generateDummyData(tournamentID);
        
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
              // Calculate the score difference
              const oldScores = court.scores;
              const scoreDifferences = newScores.map((score, index) => score - oldScores[index]);
              
              // Update player points
              court.teams.forEach((team, teamIndex) => {
                team.forEach(player => {
                  const playerIndex = newPlayers.findIndex(p => p.Name === player.Name);
                  if (playerIndex !== -1) {
                    newPlayers[playerIndex].Points += scoreDifferences[teamIndex];
                  }
                });
              });
              
              // Update the court with new scores and previous scores
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
