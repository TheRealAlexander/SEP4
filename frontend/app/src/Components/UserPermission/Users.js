import React from 'react';
import { Typography, TableContainer, Paper, Table, TableHead, TableRow, TableCell, TableBody, Checkbox } from '@mui/material';

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

export default Users;
