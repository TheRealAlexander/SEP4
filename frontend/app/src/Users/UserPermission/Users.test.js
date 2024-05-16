import React from 'react';
import { render, screen, fireEvent } from '@testing-library/react';
import Users from './Users';

describe('Users component', () => {
  it('toggles super user status on checkbox click', () => {
    const handleSuperUserToggle = jest.fn();
    const users = [{ id: 1, name: 'John Doe' }, { id: 2, name: 'Jane Smith' }];
    const superUserIds = [];

    render(<Users users={users} superUserIds={superUserIds} handleSuperUserToggle={handleSuperUserToggle} />);

    const checkboxes = screen.getAllByRole('checkbox'); // Getting all checkboxes
    fireEvent.click(checkboxes[0]); // Click the first checkbox
    expect(handleSuperUserToggle).toHaveBeenCalledWith(users[0].id);

    fireEvent.click(checkboxes[0]); // Click again to simulate toggle off
    expect(handleSuperUserToggle).toHaveBeenCalledTimes(2); // Checking call count for toggling
  });
});
