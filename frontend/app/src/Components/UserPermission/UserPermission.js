import React, { useState } from 'react';
import { useNavigate } from 'react-router-dom';
import AdminUsers from './AdminUsers';
import Users from './Users';
import UserChangeDialog from './ConfirmationDialogWindow';
import { Button, Box } from '@mui/material';

const UserList = ({ adminUsers, superUsers, standardUsers }) => {
  const [superUserIds, setSuperUserIds] = useState(superUsers.map(user => user.id));
  const [updatedSuperUserIds, setUpdatedSuperUserIds] = useState([]);
  const [isDialogOpen, setDialogOpen] = useState(false);
  const navigate = useNavigate();

  const handleSuperUserToggle = (userId) => {
    if (superUserIds.includes(userId)) {
      setSuperUserIds(superUserIds.filter(id => id !== userId));
    } else {
      setSuperUserIds([...superUserIds, userId]);
    }
    setUpdatedSuperUserIds(current =>
      current.includes(userId) ? current.filter(id => id !== userId) : [...current, userId]
    );
  };

  const handleOpenDialog = () => {
    setDialogOpen(true);
  };

  const handleCloseDialog = () => {
    setDialogOpen(false);
    navigate('/rerender', { replace: true }); // Navigate to a base or another route temporarily
    setTimeout(() => {
      navigate('/users', { replace: true }); // Navigate back to /users
    }, 1); // Short delay to allow the first navigation to complete
  };

  const handleConfirmChanges = () => {
    // Perform saving logic here
    console.log("Updated User IDs:", updatedSuperUserIds);
    setUpdatedSuperUserIds([]);
    setDialogOpen(false);
  };

  const handleRemoveUser = (userId) => {
    setUpdatedSuperUserIds(current => current.filter(id => id !== userId));
  };

  const upgradedUsers = updatedSuperUserIds.filter(id => superUserIds.includes(id)).map(id => ({
    id,
    name: superUsers.concat(standardUsers).find(user => user.id === id)?.name
  }));

  const downgradedUsers = updatedSuperUserIds.filter(id => !superUserIds.includes(id)).map(id => ({
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
        <Button variant="contained" onClick={handleOpenDialog} disabled={updatedSuperUserIds.length === 0}>
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
