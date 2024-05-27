import axios from 'axios';
import UserService from './UserService';

jest.mock('axios', () => ({
    post: jest.fn(),
    get: jest.fn(),
    put: jest.fn(),
    delete: jest.fn(),
  }));

describe('UserService', () => {
  afterEach(() => {
    jest.clearAllMocks();
  });

  it('fetches super users', async () => {
    const data = { data: ['user1', 'user2'] };
    axios.get.mockResolvedValue(data);

    const result = await UserService.fetchSuperUsers();

    expect(result).toEqual(data.data);
    expect(axios.get).toHaveBeenCalledWith('http://broker:5202/broker/superUsers');
  });

  it('fetches non-admin users', async () => {
    const data = { data: ['user3', 'user4'] };
    axios.get.mockResolvedValue(data);

    const result = await UserService.fetchNonAdminUsers();

    expect(result).toEqual(data.data);
    expect(axios.get).toHaveBeenCalledWith('http://broker:5202/broker/nonSuperUsers');
  });

  it('adjusts user permissions', async () => {
    const data = { data: 'success' };
    const usersToChange = { userId: '1', isAdmin: true };
    const token = 'testToken';
    axios.put.mockResolvedValue(data);
    localStorage.setItem('token', token);

    const result = await UserService.adjustUserPermissions(usersToChange);

    expect(result).toEqual(data.data);
    expect(axios.put).toHaveBeenCalledWith(
      `http://broker:5202/broker/users/adjustUserPermissions/${usersToChange}`,
      { ...usersToChange },
      { headers: { Authorization: `Bearer ${token}` } }
    );
  });
});