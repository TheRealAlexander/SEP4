import React from 'react';
import {Grid, Avatar, Typography} from '@mui/material';
import { Button, Paper, TextField } from '@mui/material';
import LockOutlinedIcon from '@mui/icons-material/LockOutlined';
import { Link } from 'react-router-dom';

const Login = () => {

    const paperStyle = {padding: 20, height: '70vh', width: 280, margin: '20px auto'}
    const avatarStyle = {backgroundColor: 'Lightblue'}
    const buttonStyle = {margin: '8px 0'}
    return (    
        <Grid container justify="center" alignItems="center" style={{ minHeight: '100vh' }}>
            <Paper elevation={10} style={paperStyle}>
                <Grid align='center'>
                    <Avatar style={avatarStyle}><LockOutlinedIcon/></Avatar>
                    <h2>Sign In</h2>
                </Grid>
                <TextField label='Username' placeholder='Enter username' fullWidth required sx={{ marginBottom: 2 }}/>
                <TextField label='Password' placeholder='Enter password' type='password' fullWidth required sx={{ marginBottom: 2 }}/>
                
                <Button type='submit' color='primary' variant='contained' style={buttonStyle} fullWidth>Sign in</Button>

                <Typography>
                   Don't have an account? <Link to="/registration">Sign Up</Link>
                </Typography>
            </Paper>
        </Grid>
    );
}

export default Login;