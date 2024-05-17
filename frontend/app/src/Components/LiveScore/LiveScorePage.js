import React, { useEffect, useState } from "react";
import { Box } from "@mui/material";
import LiveScoreService from "../../Services/LiveScoreService";
import { Card, CardContent, Typography, CircularProgress } from "@mui/material";

const LiveScorePage = () => {
  const [matches, setMatches] = useState([]);
  const [selectedMatch, setSelectedMatch] = useState(null);
  const [error, setError] = useState(null);

  useEffect(() => {
    const fetchMatches = async () => {
      try {
        const allMatches = await LiveScoreService.getAllMatches();
        setMatches(allMatches);
      } catch (error) {
        setError(error.message);
      }
    };

    fetchMatches();
  }, []);

  if (error) {
    return <Typography>Error: {error}</Typography>;
  }

  if (matches.length === 0) {
    return <Typography>No matches</Typography>;
  }

  const handleMatchClick = (id) => {
    setSelectedMatch((prevMatch) =>
      prevMatch && prevMatch.id === id
        ? null
        : matches.find((match) => match.id === id)
    );
  };
  return (
    <Box
      sx={{
        display: "grid",
        placeItems: "center",
        height: "100vh",
        width: "100vw",
      }}
    >
      <Box
        sx={{
          display: "flex",
          flexDirection: "column",
          gap: 2.5,
          width: "100%",
          maxWidth: 500,
          minWidth: 300,
        }}
      >
        {matches.length > 0 ? (
          matches.map((match) => (
            <Card
              key={match.id}
              onClick={() => handleMatchClick(match.id)}
              sx={{
                margin: 2.5,
                cursor: "pointer",
                boxShadow: "0 0 10px 0.1px #3f51b5",
              }}
            >
              <CardContent>
                <Typography variant="h5" sx={{ textAlign: "center" }}>
                  {match.name}
                </Typography>
                <Typography color="textSecondary">{match.date}</Typography>
                <Typography color="textSecondary">{match.score}</Typography>
                {selectedMatch && selectedMatch.id === match.id && (
                  <>
                    <Typography color="textSecondary">{`Field: ${match.field}`}</Typography>
                    <Typography color="textSecondary">{`Start Time: ${match.startTime}`}</Typography>
                  </>
                )}
              </CardContent>
            </Card>
          ))
        ) : (
          <CircularProgress />
        )}
      </Box>
    </Box>
  );
};

export default LiveScorePage;
