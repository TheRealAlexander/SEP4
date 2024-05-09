import React, { useState } from 'react';
import AdminUsers from './AdminUsers';
import Users from './Users';
import UserChangeDialog from './ConfirmationDialogWindow';
import { Button, Box } from '@mui/material';

const UserList = ({ adminUsers, superUsers, standardUsers }) => {
  const [superUserIds, setSuperUserIds] = useState(superUsers.map(user => user.id));
  const [originalSuperUserIds, setOriginalSuperUserIds] = useState(superUsers.map(user => user.id));
  const [updatedSuperUserIds, setUpdatedSuperUserIds] = useState([]);
  const [isDialogOpen, setDialogOpen] = useState(false);

  const handleSuperUserToggle = (userId) => {
    const isCurrentlySuper = superUserIds.includes(userId);
    if (isCurrentlySuper) {
      setSuperUserIds(current => current.filter(id => id !== userId));
    } else {
      setSuperUserIds(current => [...current, userId]);
    }
    setUpdatedSuperUserIds(current =>
      current.includes(userId) ? current.filter(id => id !== userId) : [...current, userId]
    );
  };

  const handleRemoveUser = (userId) => {
    setUpdatedSuperUserIds(current => current.filter(id => id !== userId));
    setSuperUserIds(current => current.includes(userId) ? current.filter(id => id !== userId) : current);
  };

  const handleConfirmChanges = () => {
    setOriginalSuperUserIds(superUserIds);
    setUpdatedSuperUserIds([]);
    setDialogOpen(false);
  };

  const handleCloseDialog = () => {
    setSuperUserIds(originalSuperUserIds);
    setUpdatedSuperUserIds([]);
    setDialogOpen(false);
  };

  const upgradedUsers = updatedSuperUserIds.filter(id => originalSuperUserIds.includes(id)).map(id => ({
    id,
    name: superUsers.concat(standardUsers).find(user => user.id === id)?.name
  }));

  const downgradedUsers = updatedSuperUserIds.filter(id => !originalSuperUserIds.includes(id)).map(id => ({
    id,
    name: superUsers.concat(standardUsers).find(user => user.id === id)?.name
  }));

  return (
    <div>
      <AdminUsers users={adminUsers} />
      <Users
        users={[...superUsers, ...standardUsers]}
        superUserIds={superUserIds}
        handleSuperUserToggle={handleSuperUserToggle}
      />
      <Box display="flex" justifyContent="flex-end" mt={2}>
        <Button variant="contained" onClick={() => setDialogOpen(true)} disabled={updatedSuperUserIds.length === 0}>
          Save Changes
        </Button>
      </Box>
      <UserChangeDialog
        isOpen={isDialogOpen}
        handleClose={handleCloseDialog}
        upgradedUsers={upgradedUsers}
        downgradedUsers={downgradedUsers}
        handleConfirmChanges={handleConfirmChanges}
        handleRemoveUser={handleRemoveUser}
      />
    </div>
  );
};

export default UserList;
