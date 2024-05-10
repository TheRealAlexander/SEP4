import React from 'react';
import { render, fireEvent, waitFor, screen } from '@testing-library/react';
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

    fireEvent.change(screen.getByLabelText(/username/i), { target: { value: 'testuser' } });
    fireEvent.change(screen.getByLabelText(/password/i), { target: { value: 'testpass' } });

    fireEvent.click(screen.getByRole('button', { name: /sign in/i }));

    await waitFor(() => {
      expect(AuthService.login).toHaveBeenCalledWith('testuser', 'testpass');
    });
  });
});