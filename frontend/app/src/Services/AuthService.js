import axios from "axios";

const API_URL = "/Broker";

export const register = (username, password, email, age) => {
  return axios
    .post(API_URL + "/register", {
      username,
      password,
      email,
      age,
    })
    .then((response) => response.data)
    .catch((error) => {
      throw error.response ? error.response.data : error;
    });
};

export const login = (username, password) => {
  return axios
    .post(API_URL + "/login", {
      username,
      password,
    })
    .then((response) => {
      const data = response.data;
      if (data) {
        localStorage.setItem("user", JSON.stringify(data));
      }
      return data;
    })
    .catch((error) => {
      throw error.response ? error.response.data : error;
    });
};

export const logout = () => {
  localStorage.removeItem("user");
};

export const getCurrentUser = () => {
  return JSON.parse(localStorage.getItem("user"));
};
