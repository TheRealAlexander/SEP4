const API_URL = "http://localhost:8000/api/auth/" //Placeholder for the API URL

const register = (username, password) => {
    return fetch(API_URL + "register", {
      method: 'POST',
      headers: {
        'Content-Type': 'application/json',
      },
      body: JSON.stringify({
        username,
        password,
      }),
    }).then(response => response.json());
};

const login = (username, password) => {
    return fetch(API_URL + "login", {
      method: 'POST',
      headers: {
        'Content-Type': 'application/json',
      },
      body: JSON.stringify({
        username,
        password,
      }),
    }).then(response => response.json())
      .then(data => {
        if (data.accessToken) {
          localStorage.setItem("user", JSON.stringify(data));
        }
        return data;
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