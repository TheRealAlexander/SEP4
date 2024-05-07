import React from 'react';
import { render, fireEvent, waitFor } from '@testing-library/react';
import { useNavigate } from 'react-router-dom';
import AuthService from '../../Services/AuthService';
import Registration from './Registration';
import { BrowserRouter as Router } from 'react-router-dom';

jest.mock('../../Services/AuthService', () => ({
    register: jest.fn().mockReturnValue(Promise.resolve()),
  }));

jest.mock('react-router-dom', () => ({
  ...jest.requireActual('react-router-dom'),
  useNavigate: jest.fn(),
}));

describe('Registration', () => {
  it('calls AuthService.register with the correct arguments when the form is submitted', async () => {
    const mockNavigate = jest.fn();
    useNavigate.mockReturnValue(mockNavigate);

    const { getByLabelText, getByRole } = render(
        <Router>
          <Registration />
        </Router>
      );

    const usernameInput = getByLabelText(/username/i);
    const passwordInput = getByLabelText(/password/i);
    const submitButton = getByRole('button', { name: /register/i });

    fireEvent.change(usernameInput, { target: { value: 'testuser' } });
    fireEvent.change(passwordInput, { target: { value: 'testpass' } });
    fireEvent.click(submitButton);

    await waitFor(() => {
      expect(AuthService.register).toHaveBeenCalledWith('testuser', 'testpass');
    });
  });
});