import React from 'react';
import { render, screen, fireEvent } from '@testing-library/react';
import UserEvent from '@testing-library/user-event';
import UserChangeDialog from './ConfirmationDialogWindow';

describe('UserChangeDialog component', () => {
  const upgradedUsers = [{ id: 1, name: 'John Doe' }];
  const downgradedUsers = [{ id: 2, name: 'Jane Smith' }];
  const handleConfirmChanges = jest.fn();
  const handleRemoveUser = jest.fn();
  const handleClose = jest.fn();

  it('confirms changes correctly', () => {
    render(
      <UserChangeDialog
        isOpen={true}
        upgradedUsers={upgradedUsers}
        downgradedUsers={downgradedUsers}
        handleConfirmChanges={handleConfirmChanges}
        handleRemoveUser={handleRemoveUser}
        handleClose={handleClose}
      />
    );

    const confirmButton = screen.getByRole('button', { name: 'Confirm' });
    fireEvent.click(confirmButton);
    expect(handleConfirmChanges).toHaveBeenCalled();
  });

  it('removes a user correctly', () => {
    render(
      <UserChangeDialog
        isOpen={true}
        upgradedUsers={upgradedUsers}
        downgradedUsers={downgradedUsers}
        handleConfirmChanges={handleConfirmChanges}
        handleRemoveUser={handleRemoveUser}
        handleClose={handleClose}
      />
    );
  
    const removeButtons = screen.getAllByRole('button', { name: 'Remove' });
    // Assuming you want to click the 'Remove' for the first upgraded user
    fireEvent.click(removeButtons[0]);
    expect(handleRemoveUser).toHaveBeenCalledWith(upgradedUsers[0].id);
  })});  
