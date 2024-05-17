import { useState, useEffect } from "react";
import axios from "axios";

const API_BASE_URL = "http://broker:5202";

const useNextRound = (tournamentID) => {
  const [nextRound, setNextRound] = useState(null);
  const [loading, setLoading] = useState(true);
  const [error, setError] = useState(null);

  useEffect(() => {
    const fetchNextRound = async () => {
      try {
        const response = await axios.get(
          `${API_BASE_URL}/broker/tournaments/${tournamentID}/nextRound`
        );
        setNextRound(response.data);
        setLoading(false);
      } catch (err) {
        setError(err);
        setLoading(false);
      }
    };

    fetchNextRound();
  }, [tournamentID]);

  let dummyRound = {
    round: {
      id: 1,
      courts: [
        {
          court_id: 1,
          participants: [
            [
              { id: 1, name: "Team A1" },
              { id: 2, name: "Team A2" },
            ],
            [
              { id: 3, name: "Team B1" },
              { id: 4, name: "Team B2" },
            ],
          ],
        },
        {
          court_id: 2,
          participants: [
            [
              { id: 5, name: "Team C1" },
              { id: 6, name: "Team C2" },
            ],
            [
              { id: 7, name: "Team D1" },
              { id: 8, name: "Team D2" },
            ],
          ],
        },
      ],
    },
  };

  return { dummyRound, loading, error };
};

export default useNextRound;
