import { useState, useEffect } from 'react';
import axios from 'axios';

const API_BASE_URL = "http://broker:5202";

const useNextRound = (tournamentID) => {
  const [nextRound, setNextRound] = useState(null);
  const [scores, setScores] = useState([]);
  const [loading, setLoading] = useState(true);
  const [error, setError] = useState(null);

  useEffect(() => {
    const fetchNextRound = async () => {
      try {
        // Use the provided dummy JSON
        const dummyRound = {
          tournamentID: 1,
          rounds: [
            {
              id: 1,
              courts: [
                {
                  id: 1,
                  players: [
                    [
                      { id: 1, name: "Player 1" },
                      { id: 2, name: "Player 2" }
                    ],
                    [
                      { id: 3, name: "Player 3" },
                      { id: 4, name: "Player 4" }
                    ]
                  ],
                  score1: 0,
                  score2: 0
                },
                {
                  id: 2,
                  players: [
                    [
                      { id: 5, name: "Player 5" },
                      { id: 6, name: "Player 6" }
                    ],
                    [
                      { id: 7, name: "Player 7" },
                      { id: 8, name: "Player 8" }
                    ]
                  ],
                  score1: 0,
                  score2: 0
                },
                {
                  id: 3,
                  players: [
                    [
                      { id: 9, name: "Player 9" },
                      { id: 10, name: "Player 10" }
                    ],
                    [
                      { id: 11, name: "Player 11" },
                      { id: 12, name: "Player 12" }
                    ]
                  ],
                  score1: 0,
                  score2: 0
                },
                {
                  id: 4,
                  players: [
                    [
                      { id: 13, name: "Player 13" },
                      { id: 14, name: "Player 14" }
                    ],
                    [
                      { id: 15, name: "Player 15" },
                      { id: 16, name: "Player 16" }
                    ]
                  ],
                  score1: 0,
                  score2: 0
                },
                {
                  id: 5,
                  players: [
                    [
                      { id: 17, name: "Player 17" },
                      { id: 18, name: "Player 18" }
                    ],
                    [
                      { id: 19, name: "Player 19" },
                      { id: 20, name: "Player 20" }
                    ]
                  ],
                  score1: 0,
                  score2: 0
                },
                {
                  id: 6,
                  players: [
                    [
                      { id: 21, name: "Player 21" },
                      { id: 22, name: "Player 22" }
                    ],
                    [
                      { id: 23, name: "Player 23" },
                      { id: 24, name: "Player 24" }
                    ]
                  ],
                  score1: 0,
                  score2: 0
                },
                {
                  id: 7,
                  players: [
                    [
                      { id: 25, name: "Player 25" },
                      { id: 26, name: "Player 26" }
                    ],
                    [
                      { id: 27, name: "Player 27" },
                      { id: 28, name: "Player 28" }
                    ]
                  ],
                  score1: 0,
                  score2: 0
                },
                {
                  id: 8,
                  players: [
                    [
                      { id: 29, name: "Player 29" },
                      { id: 30, name: "Player 30" }
                    ],
                    [
                      { id: 31, name: "Player 31" },
                      { id: 32, name: "Player 32" }
                    ]
                  ],
                  score1: 0,
                  score2: 0
                },
                {
                  id: 9,
                  players: [
                    [
                      { id: 33, name: "Player 33" },
                      { id: 34, name: "Player 34" }
                    ],
                    [
                      { id: 35, name: "Player 35" },
                      { id: 36, name: "Player 36" }
                    ]
                  ],
                  score1: 0,
                  score2: 0
                },
                {
                  id: 10,
                  players: [
                    [
                      { id: 37, name: "Player 37" },
                      { id: 38, name: "Player 38" }
                    ],
                    [
                      { id: 39, name: "Player 39" },
                      { id: 40, name: "Player 40" }
                    ]
                  ],
                  score1: 0,
                  score2: 0
                },
                {
                  id: 11,
                  players: [
                    [
                      { id: 41, name: "Player 41" },
                      { id: 42, name: "Player 42" }
                    ],
                    [
                      { id: 43, name: "Player 43" },
                      { id: 44, name: "Player 44" }
                    ]
                  ],
                  score1: 0,
                  score2: 0
                },
                {
                  id: 12,
                  players: [
                    [
                      { id: 45, name: "Player 45" },
                      { id: 46, name: "Player 46" }
                    ],
                    [
                      { id: 47, name: "Player 47" },
                      { id: 48, name: "Player 48" }
                    ]
                  ],
                  score1: 0,
                  score2: 0
                },
                {
                  id: 13,
                  players: [
                    [
                      { id: 49, name: "Player 49" },
                      { id: 50, name: "Player 50" }
                    ],
                    [
                      { id: 51, name: "Player 51" },
                      { id: 52, name: "Player 52" }
                    ]
                  ],
                  score1: 0,
                  score2: 0
                },
                {
                  id: 14,
                  players: [
                    [
                      { id: 53, name: "Player 53" },
                      { id: 54, name: "Player 54" }
                    ],
                    [
                      { id: 55, name: "Player 55" },
                      { id: 56, name: "Player 56" }
                    ]
                  ],
                  score1: 0,
                  score2: 0
                },
                {
                  id: 15,
                  players: [
                    [
                      { id: 57, name: "Player 57" },
                      { id: 58, name: "Player 58" }
                    ],
                    [
                      { id: 59, name: "Player 59" },
                      { id: 60, name: "Player 60" }
                    ]
                  ],
                  score1: 0,
                  score2: 0
                },
                {
                  id: 16,
                  players: [
                    [
                      { id: 61, name: "Player 61" },
                      { id: 62, name: "Player 62" }
                    ],
                    [
                      { id: 63, name: "Player 63" },
                      { id: 64, name: "Player 64" }
                    ]
                  ],
                  score1: 0,
                  score2: 0
                }
              ]
            }
          ],
          scores: [
            { id: 1, name: "Player 1", score: 10 },
            { id: 2, name: "Player 2", score: 10 },
            { id: 3, name: "Player 3", score: 15 },
            { id: 4, name: "Player 4", score: 15 },
            { id: 5, name: "Player 5", score: 12 },
            { id: 6, name: "Player 6", score: 12 },
            { id: 7, name: "Player 7", score: 18 },
            { id: 8, name: "Player 8", score: 18 },
            { id: 9, name: "Player 9", score: 20 },
            { id: 10, name: "Player 10", score: 20 },
            { id: 11, name: "Player 11", score: 22 },
            { id: 12, name: "Player 12", score: 22 },
            { id: 13, name: "Player 13", score: 25 },
            { id: 14, name: "Player 14", score: 25 },
            { id: 15, name: "Player 15", score: 28 },
            { id: 16, name: "Player 16", score: 28 },
            { id: 17, name: "Player 17", score: 30 },
            { id: 18, name: "Player 18", score: 30 },
            { id: 19, name: "Player 19", score: 32 },
            { id: 20, name: "Player 20", score: 32 },
            { id: 21, name: "Player 21", score: 34 },
            { id: 22, name: "Player 22", score: 34 },
            { id: 23, name: "Player 23", score: 36 },
            { id: 24, name: "Player 24", score: 36 },
            { id: 25, name: "Player 25", score: 38 },
            { id: 26, name: "Player 26", score: 38 },
            { id: 27, name: "Player 27", score: 40 },
            { id: 28, name: "Player 28", score: 40 },
            { id: 29, name: "Player 29", score: 42 },
            { id: 30, name: "Player 30", score: 42 },
            { id: 31, name: "Player 31", score: 44 },
            { id: 32, name: "Player 32", score: 44 },
            { id: 33, name: "Player 33", score: 46 },
            { id: 34, name: "Player 34", score: 46 },
            { id: 35, name: "Player 35", score: 48 },
            { id: 36, name: "Player 36", score: 48 },
            { id: 37, name: "Player 37", score: 50 },
            { id: 38, name: "Player 38", score: 50 },
            { id: 39, name: "Player 39", score: 52 },
            { id: 40, name: "Player 40", score: 52 },
            { id: 41, name: "Player 41", score: 54 },
            { id: 42, name: "Player 42", score: 54 },
            { id: 43, name: "Player 43", score: 56 },
            { id: 44, name: "Player 44", score: 56 },
            { id: 45, name: "Player 45", score: 58 },
            { id: 46, name: "Player 46", score: 58 },
            { id: 47, name: "Player 47", score: 60 },
            { id: 48, name: "Player 48", score: 60 },
            { id: 49, name: "Player 49", score: 62 },
            { id: 50, name: "Player 50", score: 62 },
            { id: 51, name: "Player 51", score: 64 },
            { id: 52, name: "Player 52", score: 64 },
            { id: 53, name: "Player 53", score: 66 },
            { id: 54, name: "Player 54", score: 66 },
            { id: 55, name: "Player 55", score: 68 },
            { id: 56, name: "Player 56", score: 68 },
            { id: 57, name: "Player 57", score: 70 },
            { id: 58, name: "Player 58", score: 70 },
            { id: 59, name: "Player 59", score: 72 },
            { id: 60, name: "Player 60", score: 72 },
            { id: 61, name: "Player 61", score: 74 },
            { id: 62, name: "Player 62", score: 74 },
            { id: 63, name: "Player 63", score: 76 },
            { id: 64, name: "Player 64", score: 76 }
          ]
        };

        // Simulate a delay to mimic an API call
        await new Promise(resolve => setTimeout(resolve, 1000));

        setNextRound(dummyRound);
        setScores(dummyRound.scores);
        setLoading(false);
      } catch (err) {
        setError(err);
        setLoading(false);
      }
    };

    fetchNextRound();
  }, [tournamentID]);

  return { nextRound, scores, loading, error };
};

export default useNextRound;
