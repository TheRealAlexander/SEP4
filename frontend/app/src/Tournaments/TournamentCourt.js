import React, { useState, useEffect } from "react";
import { Card as MuiCard, CardContent, Typography, Box, Divider } from "@mui/material";
import TeamColumn from "./CourtComponents/TeamColumn";
import CourtScore from "./CourtComponents/CourtScore";
import ScoreDialog from "./CourtComponents/ScoreDialog";

const TournamentCourt = ({ court, onUpdate, open, handleClose, handleClick, pointsPerMatch, index }) => {
  const [tempScore, setTempScore] = useState([0, 0]);
  const [errors, setErrors] = useState([null, null]);

  useEffect(() => {
    setTempScore(court.scores || [0, 0]);
  }, [court.scores]);

  const handleUpdate = () => {
    if (validateScores(tempScore)) {
      onUpdate(court.id, tempScore);
      handleClose();
    }
  };

  const validateScores = (scores) => {
    const newErrors = [null, null];
    let valid = true;

    scores.forEach((score, index) => {
      if (score < 0) {
        newErrors[index] = "Score cannot be less than 0";
        valid = false;
      } else if (score > pointsPerMatch) {
        newErrors[index] = `Score cannot be greater than ${pointsPerMatch}`;
        valid = false;
      } else if (scores[0] + scores[1] > pointsPerMatch) {
        newErrors[index] = `Total score cannot exceed ${pointsPerMatch}`;
        valid = false;
      }
    });

    setErrors(newErrors);
    return valid;
  };

  if (!court || !court.teams || court.teams.length < 2 || !court.teams[0] || !court.teams[1]) {
    return <div>Loading or incomplete data...</div>;
  }

  return (
    <MuiCard
      variant="outlined"
      onClick={handleClick}
      sx={{
        width: "100%",
        transition: "transform 0.2s, box-shadow 0.2s",
        "&:hover": {
          transform: "scale(1.05)",
          boxShadow: "0px 10px 15px rgba(0,0,0,0.3)",
        },
      }}
    >
      <CardContent sx={{ textAlign: "center" }}>
        <Typography variant="h6" gutterBottom>
          {" "}
          Court #{index + 1}{" "}
        </Typography>
        <Divider />
        <Box sx={{ display: "flex", justifyContent: "space-between", alignItems: "center" }}>
          <TeamColumn team={court.teams[0]} />
          <Typography variant="h6">vs</Typography>
          <TeamColumn team={court.teams[1]} />
        </Box>
        <CourtScore>
          {tempScore[0]} - {tempScore[1]}
        </CourtScore>
      </CardContent>
      <ScoreDialog
        open={open}
        handleClose={handleClose}
        handleUpdate={handleUpdate}
        pointsPerMatch={pointsPerMatch}
        court={court}
        tempScore={tempScore}
        setTempScore={setTempScore}
        errors={errors}
        setErrors={setErrors}
        index={index}
      />
    </MuiCard>
  );
};

export default TournamentCourt;
