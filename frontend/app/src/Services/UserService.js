import axios from 'axios';

class UserService {
  // Fetch all users
  static async fetchUsers() {
    try {
      const response = await axios.get('http://localhost:8000/users');
      return response.data;
    } catch (error) {
      console.error(error);
    }
  }

  // Update user
  static async makeUserAdmin(userToMakeAdmin) {
    try {
      const user = JSON.parse(localStorage.getItem('user'));
      const response = await axios.put(`http://localhost:8000/users/admins/${user.id}`, {
        ...user,
        ...userToMakeAdmin
      });
      return response.data;
    } catch (error) {
      console.error(error);
    }
  }

  static async enableUserToCreateTournaments(userToChange) {
    try {
      const user = JSON.parse(localStorage.getItem('user'));
      const response = await axios.put(`http://localhost:8000/users/tournamentUsers/${user.id}`, {
        ...user,
        ...userToChange
      });
      return response.data;
    } catch (error) {
      console.error(error);
    }
  }
}

export default UserService;