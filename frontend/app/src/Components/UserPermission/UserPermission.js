import React, { useState } from 'react';
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
  Box
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
          {users.map((user, index) => (
            <TableRow key={user.id} style={{ backgroundColor: index % 2 === 0 ? '#f5f5f5' : 'inherit' }}>
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

  const handleSuperUserToggle = (userId) => {
    if (superUserIds.includes(userId)) {
      setSuperUserIds(superUserIds.filter(id => id !== userId));
    } else {
      setSuperUserIds([...superUserIds, userId]);
    }

    // Store the updated userIds
    if (!updatedSuperUserIds.includes(userId)) {
      setUpdatedSuperUserIds([...updatedSuperUserIds, userId]);
    } else {
      setUpdatedSuperUserIds(updatedSuperUserIds.filter(id => id !== userId));
    }
  };

  const handleSaveChanges = () => {
    // Here you can send the updatedSuperUserIds list to the backend
    console.log("Updated User IDs:", updatedSuperUserIds);
    // Reset the updatedSuperUserIds list after saving changes
    setUpdatedSuperUserIds([]);
  };

  return (
    <div>
      <AdminUsers users={adminUsers} />

      <Users
        users={[...superUsers, ...standardUsers]}
        superUserIds={superUserIds}
        handleSuperUserToggle={handleSuperUserToggle}
      />

      <Box display="flex" justifyContent="flex-end" mt={2}>
        <Button variant="contained" onClick={handleSaveChanges} disabled={updatedSuperUserIds.length === 0}>
          Save Changes
        </Button>
      </Box>
    </div>
  );
};

export default UserList;
