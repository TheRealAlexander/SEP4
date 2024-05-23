import React from "react";
import { Box, Typography } from "@mui/material";

const TeamColumn = ({ team }) => (
  <Box
    sx={{
      display: "flex",
      flexDirection: "column",
      alignItems: "center",
      justifyContent: "center",
      margin: 1,
      width: "100px",
    }}
  >
    {team &&
      team.map((player, index) => (
        <Typography key={index} variant="body1" fontWeight="bold">
          {player?.Name || "Unknown Player"}
        </Typography>
      ))}
  </Box>
);

export default TeamColumn;
