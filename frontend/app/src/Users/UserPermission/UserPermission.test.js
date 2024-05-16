import React from 'react';
import { render, fireEvent, screen } from '@testing-library/react';
import { UserList } from './UserPermission';

describe('UserList Component', () => {
  const adminUsers = [{ id: 1, name: 'Admin1' }];
  const superUsers = [{ id: 2, name: 'SuperUser1' }];
  const standardUsers = [{ id: 3, name: 'StandardUser1' }];

  beforeEach(() => {
    render(<UserList adminUsers={adminUsers} superUsers={superUsers} standardUsers={standardUsers} />);
  });

  it('renders checkboxes correctly based on superUsers prop', () => {
    const superUserCheckbox = screen.getByLabelText('SuperUser1');
    const standardUserCheckbox = screen.getByLabelText('StandardUser1');

    expect(superUserCheckbox.checked).toBe(true); // Should be checked as it's a super user
    expect(standardUserCheckbox.checked).toBe(false); // Should not be checked as it's not a super user
  });

  it('updates super user status on confirmation', () => {
    const standardUserCheckbox = screen.getByLabelText('StandardUser1');

    // Simulate changing super user status
    fireEvent.click(standardUserCheckbox); // Mark as super user
    fireEvent.click(screen.getByText('Save Changes')); // Open dialog
    fireEvent.click(screen.getByText('Confirm')); // Confirm changes

    expect(standardUserCheckbox.checked).toBe(true); // Should now be checked
  });

  it('reverts changes when cancel is clicked', () => {
    const superUserCheckbox = screen.getByLabelText('SuperUser1');
    const standardUserCheckbox = screen.getByLabelText('StandardUser1');

    // Initial state checks
    expect(superUserCheckbox.checked).toBe(true);
    expect(standardUserCheckbox.checked).toBe(false);

    // Simulate changing super user status
    fireEvent.click(standardUserCheckbox); // Attempt to mark as super user
    fireEvent.click(screen.getByText('Save Changes')); // Open dialog
    fireEvent.click(screen.getByText('Cancel')); // Cancel changes

    // Check if the state has been reverted correctly
    expect(superUserCheckbox.checked).toBe(true); // Should still be checked as it was not affected
    expect(standardUserCheckbox.checked).toBe(false); // Should revert to unchecked
  });
});
