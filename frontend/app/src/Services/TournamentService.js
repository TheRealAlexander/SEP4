import axios from "axios";
import { useState, useEffect } from "react";

const API_BASE_URL = "http://broker:5202";

export function GetAllTournaments() {
  return axios.get(`${API_BASE_URL}/broker/tournaments`)
    .then(response => response.data)
    .catch(error => console.error(error));
}

export function CreateTournament(tournamentData) {
  return axios
    .post(`${API_BASE_URL}/broker/tournaments`, tournamentData)
    .then((response) => {
      return response.data;
    })
    .catch((error) => {
      console.error(error);
      throw error;
    });
}

export function UpdateTournament(tournamentData) {
  return axios
    .put(
      `${API_BASE_URL}/broker/tournaments/${tournamentData.tournamentID}`,
      tournamentData
    )
    .then((response) => {
      return response.data;
    })
    .catch((error) => {
      console.error(error);
      throw error;
    });
}

export function RemoveTournament(tournamentID) {
  return axios
    .delete(`${API_BASE_URL}/broker/tournaments/${tournamentID}`)
    .then((response) => {
      return response.data;
    })
    .catch((error) => {
      console.error(error);
      throw error;
    });
}

export function AddParticipant(tournamentID, participant) {
  return axios
    .post(
      `${API_BASE_URL}/broker/tournaments/${tournamentID}/participants`,
      participant
    )
    .then((response) => {
      return response.data;
    })
    .catch((error) => {
      console.error(error);
      throw error;
    });
}

export function RemoveParticipant(tournamentID, participant) {
  axios
    .delete(
      `${API_BASE_URL}/broker/tournaments/${tournamentID}/participants/${participant}`
    )
    .catch((error) => {
      console.error(error);
    });
}
