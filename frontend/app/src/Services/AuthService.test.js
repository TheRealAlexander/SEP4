import axios from 'axios';
import authService from './AuthService'; // replace with the path to your auth service

jest.mock('axios');
axios.post = jest.fn();

let setItemSpy, getItemSpy, removeItemSpy;

beforeAll(() => {
  setItemSpy = jest.spyOn(Storage.prototype, 'setItem');
  getItemSpy = jest.spyOn(Storage.prototype, 'getItem');
  removeItemSpy = jest.spyOn(Storage.prototype, 'removeItem');
});

describe('authService', () => {
  beforeEach(() => {
    // Clear all instances and calls to constructor and all methods:
    localStorage.clear();
    axios.post.mockClear();
    setItemSpy.mockClear();
    getItemSpy.mockClear();
    removeItemSpy.mockClear();
  });

  it('registers a user', async () => {
    const mockResponse = { data: 'mock data' };
    axios.post.mockResolvedValue(mockResponse);

    const result = await authService.register('username', 'password', 'email', 20);

    expect(axios.post).toHaveBeenCalledWith('http://localhost:5202/broker/auth/register', {
      username: 'username',
      password: 'password',
      email: 'email',
      age: 20,
    });
    expect(result).toEqual('mock data');
  });

  it('logs in a user', async () => {
    const mockResponse = { data: { accessToken: 'mock token' } };
    axios.post.mockResolvedValue(mockResponse);

    const result = await authService.login('username', 'password');

    expect(axios.post).toHaveBeenCalledWith('http://localhost:5202/broker/auth/login', {
      username: 'username',
      password: 'password',
    });
    expect(localStorage.setItem).toHaveBeenCalledWith('user', JSON.stringify(mockResponse.data));
    expect(result).toEqual(mockResponse.data);
  });

  it('logs out a user', () => {
    authService.logout();

    expect(localStorage.removeItem).toHaveBeenCalledWith('user');
  });

  it('gets the current user', () => {
    const mockUser = { username: 'username', password: 'password' };
    localStorage.setItem('user', JSON.stringify(mockUser));

    const result = authService.getCurrentUser();

    expect(result).toEqual(mockUser);
  });
});