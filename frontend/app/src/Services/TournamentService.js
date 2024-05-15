import axios from "axios";
import { useState, useEffect } from "react";

const API_BASE_URL = "http://localhost:5202";

export function GetAllTournaments() {
  const [tournaments, setTournaments] = useState([]);
  useEffect(() => {
    axios
      .get(`${API_BASE_URL}/broker/tournaments`)
      .then((response) => {
        setTournaments(response.data);
      })
      .catch((error) => {
        console.error(error);
      });
  }, []);
  return tournaments;
}

//
export function UpdateTheTournament(tournamentData) {
  axios
    .put(
      `${API_BASE_URL}/broker/tournaments/${tournamentData.tournamentID}`,
      tournamentData
    )
    .then((response) => {
      console.log(response);
    })
    .catch((error) => {
      console.error(error);
    });
}
