import React from 'react';
import { Grid, Avatar, Typography } from '@mui/material';
import { Button, Paper, TextField } from '@mui/material';
import LockOutlinedIcon from '@mui/icons-material/LockOutlined';
import { Link, Navigate } from 'react-router-dom';

import AuthService from '../../Services/AuthService';

const LoginPage = () => {
    const [username, setUsername] = React.useState('');
    const [password, setPassword] = React.useState('');
    const [error, setError] = React.useState(null);

    const paperStyle = { padding: 20, height: '70vh', width: 280, margin: '20px auto' }
    const avatarStyle = { backgroundColor: 'Lightblue' }
    const buttonStyle = { margin: '8px 0' }

    const handleLogin = async (event) => {
        event.preventDefault();
        try {
            const data = await AuthService.login(username, password);
            if (data.error) {
                setError(data.error);
            } else {
                Navigate('/');
            }
        } catch (error) {
            setError(error.message);
        }
    }

    return (
        <Grid container justify="center" alignItems="center" style={{ minHeight: '100vh' }}>
            <Paper elevation={10} style={paperStyle}>
                <Grid align='center'>
                    <Avatar style={avatarStyle}><LockOutlinedIcon /></Avatar>
                    <h2>Sign In</h2>
                </Grid>
                <form onSubmit={handleLogin}>
                    <TextField label='Username' placeholder='Enter username' fullWidth required sx={{ marginBottom: 2 }} value={username} onChange={e => setUsername(e.target.value)} />
                    <TextField label='Password' placeholder='Enter password' type='password' fullWidth required sx={{ marginBottom: 2 }} value={password} onChange={e => setPassword(e.target.value)}/>
                    {error && <Typography color='error'>{error}</Typography>}
                    <Button type='submit' color='primary' variant='contained' style={buttonStyle} fullWidth>Sign in</Button>
                </form>
                <Typography>
                    Don't have an account? <Link to="/registration">Sign Up</Link>
                </Typography>
            </Paper>
        </Grid>
    );
}

export default LoginPage;