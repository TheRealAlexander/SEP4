import React from 'react';
import {
  Typography, TableContainer, Paper, Table, TableHead, TableRow, TableCell,
  TableBody, Checkbox, FormControlLabel
} from '@mui/material';

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
                <FormControlLabel
                  control={
                    <Checkbox
                      checked={superUserIds.includes(user.id)}
                      onChange={() => handleSuperUserToggle(user.id)}
                    />
                  }
                  label={user.name}  // Label is not needed here since we have a separate TableCell for user name
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
