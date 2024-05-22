import axios from "axios";

const API_BASE_URL = "http://broker:5202/broker";

class UserService {
  // Fetch all users
  static async fetchSuperUsers() {
    try {
      const response = await axios.get(`${API_BASE_URL}/superUsers`);
      return response.data;
    } catch (error) {
      console.error(error);
    }
  }

  static async fetchNonAdminUsers() {
    try {
      const response = await axios.get(`${API_BASE_URL}/nonSuperUsers`);
      return response.data;
    } catch (error) {
      console.error(error);
    }
  }

  static async adjustUserPermissions(usersToChange) {
    try {
      const token = localStorage.getItem("token");
      const response = await axios.put(
        `${API_BASE_URL}/users/adjustUserPermissions/${usersToChange}`,
        {
          ...usersToChange,
        },
        {
          headers: {
            Authorization: `Bearer ${token}`,
          },
        }
      );
      return response.data;
    } catch (error) {
      console.error(error);
    }
  }
}

export default UserService;
