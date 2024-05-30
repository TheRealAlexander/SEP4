import React from "react";
import {
  Dialog,
  DialogActions,
  DialogContent,
  DialogTitle,
  Button,
  Typography,
  List,
  ListItem,
  ListItemText,
  Link,
} from "@mui/material";

const UserChangeDialog = ({
  isOpen,
  handleClose,
  upgradedUsers,
  downgradedUsers,
  handleConfirmChanges,
  handleRemoveUser,
}) => (
  <Dialog open={isOpen} onClose={handleClose}>
    <DialogTitle>Confirm Changes</DialogTitle>
    <DialogContent>
      <Typography variant="h6">Upgraded to Super User</Typography>
      <List>
        {upgradedUsers.map((user) => (
          <ListItem
            key={user.id}
            secondaryAction={
              <Link
                component="button"
                onClick={() => handleRemoveUser(user.id)}
                style={{ textDecoration: "underline", color: "red" }}
              >
                Remove
              </Link>
            }
          >
            <ListItemText primary={user.username} />
          </ListItem>
        ))}
      </List>
      <Typography variant="h6">Downgraded from Super User</Typography>
      <List>
        {downgradedUsers.map((user) => (
          <ListItem
            key={user.id}
            secondaryAction={
              <Link
                component="button"
                onClick={() => handleRemoveUser(user.id)}
                style={{ textDecoration: "underline", color: "red" }}
              >
                Remove
              </Link>
            }
          >
            <ListItemText primary={user.username} />
          </ListItem>
        ))}
      </List>
    </DialogContent>
    <DialogActions>
      <Button onClick={handleClose}>Cancel</Button>
      <Button onClick={handleConfirmChanges} color="primary">
        Confirm
      </Button>
    </DialogActions>
  </Dialog>
);

export default UserChangeDialog;
