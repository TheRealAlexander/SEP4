import React, { useState } from 'react';
import { useNavigate } from 'react-router-dom';
import {
  Table,
  TableBody,
  TableCell,
  TableContainer,
  TableHead,
  TableRow,
  Paper,
  Checkbox,
  Typography,
  Button,
  Box,
  Dialog,
  DialogActions,
  DialogContent,
  DialogTitle,
  List,
  ListItem,
  ListItemText
} from '@mui/material';

const AdminUsers = ({ users }) => (
  <div style={{ marginBottom: '40px' }}>
    <Typography variant="h5">Admin Users</Typography>
    <TableContainer component={Paper}>
      <Table>
        <TableHead>
          <TableRow>
            <TableCell>ID</TableCell>
            <TableCell>User Name</TableCell>
          </TableRow>
        </TableHead>
        <TableBody>
          {users.map((user, index) => (
            <TableRow key={user.id} style={{ backgroundColor: index % 2 === 0 ? '#f5f5f5' : 'inherit' }}>
              <TableCell>{user.id}</TableCell>
              <TableCell>{user.name}</TableCell>
            </TableRow>
          ))}
        </TableBody>
      </Table>
    </TableContainer>
  </div>
);

const Users = ({ users, superUserIds, handleSuperUserToggle }) => (
  <div style={{ marginBottom: '20px' }}>
    <Typography variant="h5">Users</Typography>
    <TableContainer component={Paper}>
      <Table>
        <TableHead>
          <TableRow>
            <TableCell>ID</TableCell>
            <TableCell>User Name</TableCell>
            <TableCell>Super User?</TableCell>
          </TableRow>
        </TableHead>
        <TableBody>
          {users.map((user) => (
            <TableRow key={user.id} style={{ backgroundColor: user.id % 2 === 0 ? '#f5f5f5' : 'inherit' }}>
              <TableCell>{user.id}</TableCell>
              <TableCell>{user.name}</TableCell>
              <TableCell>
                <Checkbox
                  checked={superUserIds.includes(user.id)}
                  onChange={() => handleSuperUserToggle(user.id)}
                />
              </TableCell>
            </TableRow>
          ))}
        </TableBody>
      </Table>
    </TableContainer>
  </div>
);

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

      <Dialog open={isDialogOpen} onClose={handleCloseDialog}>
        <DialogTitle>Confirm Changes</DialogTitle>
        <DialogContent>
          <Typography variant="h6">Upgraded to Super User</Typography>
          <List>
            {upgradedUsers.map(user => (
              <ListItem key={user.id}>
                <ListItemText primary={user.name} />
              </ListItem>
            ))}
          </List>
          <Typography variant="h6">Downgraded from Super User</Typography>
          <List>
            {downgradedUsers.map(user => (
              <ListItem key={user.id}>
                <ListItemText primary={user.name} />
              </ListItem>
            ))}
          </List>
        </DialogContent>
        <DialogActions>
          <Button onClick={handleCloseDialog}>Cancel</Button>
          <Button onClick={handleConfirmChanges} color="primary">Confirm</Button>
        </DialogActions>
      </Dialog>
    </div>
  );
};

export default UserList;