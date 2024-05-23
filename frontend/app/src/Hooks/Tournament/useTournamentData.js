import { useState, useEffect } from 'react';

const API_BASE_URL = "http://broker:5202";

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
          
          // Generate 8 unique players
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
        
          // Distribute players to courts for each round
          for (let roundIndex = 0; roundIndex < roundCount; roundIndex++) {
            let shuffledPlayers = [...players];
            
            // Shuffle players to ensure different team compositions per round
            for (let i = shuffledPlayers.length - 1; i > 0; i--) {
              const j = Math.floor(Math.random() * (i + 1));
              [shuffledPlayers[i], shuffledPlayers[j]] = [shuffledPlayers[j], shuffledPlayers[i]];
            }
        
            // Assign players to courts
            const courts = Array.from({ length: courtCount }, (_, courtIndex) => {
              const baseIndex = courtIndex * 4;
              return {
                teams: [
                  [shuffledPlayers[baseIndex], shuffledPlayers[baseIndex + 1]],
                  [shuffledPlayers[baseIndex + 2], shuffledPlayers[baseIndex + 3]]
                ],
                scores: [0, 0]
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

  const updateScores = (roundNumber, courtIndex, newScores) => {
    setTournamentData(prev => {
      let scoreDifferences = [0, 0]; // To track score differences
  
      // Update the rounds and courts, and determine score differences
      const newRounds = prev.Rounds.map(round => {
        if (round.RoundNumber === roundNumber) {
          const newCourts = round.Courts.map((court, index) => {
            if (index === courtIndex) {
              // Calculate score differences
              scoreDifferences = [
                newScores[0] - court.scores[0],
                newScores[1] - court.scores[1]
              ];
              return { ...court, scores: newScores };
            }
            return court;
          });
          return { ...round, Courts: newCourts };
        }
        return round;
      });
  
      // Update the players based on the score differences
      const newPlayers = prev.Players.map(player => {
        newRounds.forEach(round => {
          round.Courts.forEach(court => {
            court.teams.forEach((team, teamIndex) => {
              team.forEach(teamPlayer => {
                if (teamPlayer.Name === player.Name) {
                  player.Points += scoreDifferences[teamIndex];
                }
              });
            });
          });
        });
        return player;
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
