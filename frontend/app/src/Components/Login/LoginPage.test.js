import React from 'react';
import { render, fireEvent, waitFor } from '@testing-library/react';
import LoginPage from './LoginPage';
import AuthService from '../../Services/AuthService';
import { BrowserRouter as Router } from 'react-router-dom';

jest.mock('../../Services/AuthService', () => ({
  login: jest.fn(),
}));

describe('LoginPage', () => {
  it('calls AuthService.login with the username and password when the form is submitted', async () => {
    AuthService.login.mockResolvedValue({}); // Mock the login function to resolve to an empty object

    const { getByLabelText, getByRole } = render(
        <Router>
            <LoginPage />
        </Router>
        );

    fireEvent.change(getByLabelText(/username/i), { target: { value: 'testuser' } });
    fireEvent.change(getByLabelText(/password/i), { target: { value: 'testpass' } });

    fireEvent.click(getByRole('button', { name: /sign in/i }));

    await waitFor(() => {
      expect(AuthService.login).toHaveBeenCalledWith('testuser', 'testpass');
    });
  });
});