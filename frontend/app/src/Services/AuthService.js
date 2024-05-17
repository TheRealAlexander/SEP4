import axios from 'axios';

const API_URL = "http://localhost:5001/";

const register = (username, password, email, age) => {
    return axios.post(API_URL + "register", {
        username,
        password,
        email,
        age
    })
    .then(response => response.data)
    .catch(error => {
        throw error.response ? error.response.data : error;
    });
};

const login = (username, password) => {
    return axios.post(API_URL + "login", {
        username,
        password
    })
    .then(response => {
        const data = response.data;
        if (data.accessToken) {
            localStorage.setItem("user", JSON.stringify(data));
        }
        return data;
    })
    .catch(error => {
        throw error.response ? error.response.data : error;
    });
};

const logout = () => {
    localStorage.removeItem("user");
};

const getCurrentUser = () => {
    return JSON.parse(localStorage.getItem("user"));
};

export default {
    register,
    login,
    logout,
    getCurrentUser,
};
