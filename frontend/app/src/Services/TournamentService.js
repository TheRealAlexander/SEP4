import axios from "axios";
import { useState, useEffect } from "react";

const API_BASE_URL = "http://broker:5202";

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

export function CreateTournament(tournamentData) {
  axios
    .post(`${API_BASE_URL}/broker/tournaments`, tournamentData)
    .then((response) => {
      console.log(response);
    })
    .catch((error) => {
      console.error(error);
    });
}

export function UpdateTournament(tournamentData) {
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

export function RemoveTournament(tournamentID) {
  axios
    .delete(`${API_BASE_URL}/broker/tournaments/${tournamentID}`)
    .then((response) => {
      console.log(response);
    })
    .catch((error) => {
      console.error(error);
    });
}

export function AddParticipant(tournamentID, participant) {
  axios
    .post(
      `${API_BASE_URL}/broker/tournaments/${tournamentID}/participants`,
      participant
    )
    .then((response) => {
      console.log(response);
    })
    .catch((error) => {
      console.error(error);
    });
}

export function RemoveParticipant(tournamentID, participant) {
  axios
    .delete(
      `${API_BASE_URL}/broker/tournaments/${tournamentID}/participants/${participant}`
    )
    .then((response) => {
      console.log(response);
    })
    .catch((error) => {
      console.error(error);
    });
}
