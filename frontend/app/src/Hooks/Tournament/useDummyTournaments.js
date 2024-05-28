import { useState, useEffect } from 'react';

const useDummyTournaments = () => {
  const [tournaments, setTournaments] = useState([]);
  const [loading, setLoading] = useState(true);
  const [error, setError] = useState(null);

  useEffect(() => {
    const fetchDummyTournaments = async () => {
      try {
        // Simulate an API call with a delay
        await new Promise((resolve) => setTimeout(resolve, 1000));
        const data = [
          {
            Id: '1',
            Name: 'Summer Tournament',
            Format: 'Knockout',
            NumberOfCourts: 5,
            PointsPerMatch: 3,
            Players: [{}, {}, {}, {}, {}], // Simulate 5 players
            State: 2,
            Rounds: [],
            NextRoundNumber: 1,
            SkippedARound: [],
            SkippedLastRound: [],
            Date: '2024-06-01',
          },
          {
            Id: '2',
            Name: 'Winter Tournament',
            Format: 'Round Robin',
            NumberOfCourts: 3,
            PointsPerMatch: 5,
            Players: [{}, {}, {}], // Simulate 3 players
            State: 2,
            Rounds: [],
            NextRoundNumber: 1,
            SkippedARound: [],
            SkippedLastRound: [],
            Date: '2024-12-15',
          },
          // Add more dummy tournaments as needed
        ];
        setTournaments(data);
      } catch (err) {
        setError(err);
      } finally {
        setLoading(false);
      }
    };

    fetchDummyTournaments();
  }, []);

  return { tournaments, loading, error };
};

export default useDummyTournaments;
