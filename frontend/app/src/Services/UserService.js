import axios from 'axios';

class UserService {
  // Fetch all users
  static async fetchSuperUsers() {
    try {
      const response = await axios.get('http://localhost:8000/superUsers');
      return response.data;
    } catch (error) {
      console.error(error);
    }
  }

  static async fetchNonAdminUsers() {
    try {
      const response = await axios.get('http://localhost:8000/nonSuperUsers');
      return response.data;
    } catch (error) {
      console.error(error);
    }
  }

  static async adjustUserPermissions(usersToChange) {
    try {
      const token = localStorage.getItem('token');
      const response = await axios.put(`http://localhost:8000/users/adjustUserPermissions/${usersToChange}`, {
        ...usersToChange
      }, {
        headers: {
          'Authorization': `Bearer ${token}`
        }
      });
      return response.data;
    } catch (error) {
      console.error(error);
    }
  }
}

export default UserService;