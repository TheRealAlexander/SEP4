import React, { useState } from 'react';
import { Grid, Avatar, Typography, Paper, TextField, Button, Container } from '@mui/material';
import LockOutlinedIcon from '@mui/icons-material/LockOutlined';
import { Link } from 'react-router-dom';

const RegistrationPage = () => {
    const paperStyle = { padding: 20, height: '70vh', width: 280, margin: '20px auto' }
    const avatarStyle = { backgroundColor: 'Lightblue' }
    const buttonStyle = { margin: '8px 0' }

    const [username, setUsername] = useState('');
    const [password, setPassword] = useState('');
    const [error, setError] = useState({ username: false, password: false });

    const handleRegistration = (e) => {
        e.preventDefault();

        if (!username || !password) {
            setError({
                username: username === '',
                password: password === '',
            });
            return;
        }

        console.log('Username:', username, 'Password:', password);
        
    };

    return (
        <Grid container justifyContent="center" alignItems="center" style={{ minHeight: '100vh' }}>
            <Paper elevation={10} style={paperStyle}>
                <Grid align='center'>
                    <Avatar style={avatarStyle}><LockOutlinedIcon /></Avatar>
                    <h2>Register</h2>
                </Grid>
                <form onSubmit={handleRegistration} noValidate>
                    <TextField 
                        label='Username' 
                        placeholder='Enter username' 
                        fullWidth required 
                        value={username} 
                        onChange={(e) => setUsername(e.target.value)} 
                        error={error.username}
                        helperText={error.username ? "Username is required" : ""}
                        sx={{ marginBottom: 2 }}
                    />
                    <TextField 
                        label='Password' 
                        placeholder='Enter password' 
                        type='password' 
                        fullWidth required 
                        value={password} 
                        onChange={(e) => setPassword(e.target.value)}
                        error={error.password}
                        helperText={error.password ? "Password is required" : ""}
                        sx={{ marginBottom: 2 }}
                    />
                    <Button 
                        type='submit' 
                        color='primary' 
                        variant='contained' 
                        style={buttonStyle} 
                        fullWidth
                    >
                        Register
                    </Button>
                    <Typography sx={{ marginTop: 2 }}>
                        Already have an account? <Link to="/login">Sign in here</Link>
                    </Typography>
                </form>
            </Paper>
        </Grid>
    );
};

export default RegistrationPage;
