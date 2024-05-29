import React from "react";
import { Box } from "@mui/material";

const CourtScore = ({ children }) => (
  <Box
    sx={{
      display: "flex",
      alignItems: "center",
      justifyContent: "center",
      fontSize: "1.5rem",
      fontWeight: "bold",
      margin: 1,
    }}
  >
    {children}
  </Box>
);

export default CourtScore;
