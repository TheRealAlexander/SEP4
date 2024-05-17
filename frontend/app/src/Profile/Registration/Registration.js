import React, { useState } from 'react';
import { Grid, Avatar, Typography, Paper, TextField, Button } from '@mui/material';
import LockOutlinedIcon from '@mui/icons-material/LockOutlined';
import { Link, useNavigate } from 'react-router-dom';
import AuthService from '../../Services/AuthService';

const RegistrationPage = () => {
    const paperStyle = { padding: 20, height: 'auto', width: 280, margin: '20px auto' };
    const avatarStyle = { backgroundColor: 'Lightblue' };
    const buttonStyle = { margin: '8px 0' };

    const [username, setUsername] = useState('');
    const [password, setPassword] = useState('');
    const [email, setEmail] = useState('');
    const [age, setAge] = useState('');
    const [error, setError] = useState({ username: false, password: false, email: false, age: false });

    const navigate = useNavigate();

    const handleRegistration = (e) => {
        e.preventDefault();

        if (!username || !password || !email || !age) {
            setError({
                username: username === '',
                password: password === '',
                email: email === '',
                age: age === '',
            });
            return;
        }

        AuthService.register({ username, password, email, age })
        .then(data => {
            console.log(data);
            navigate('/login');
        })
        .catch(err => {
            console.error('Registration failed', err);
            // Here you can handle errors, for example show a notification to the user
        });
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
                    <TextField 
                        label='Email' 
                        placeholder='Enter email' 
                        type='email' 
                        fullWidth required 
                        value={email} 
                        onChange={(e) => setEmail(e.target.value)}
                        error={error.email}
                        helperText={error.email ? "Email is required" : ""}
                        sx={{ marginBottom: 2 }}
                    />
                    <TextField 
                        label='Age' 
                        placeholder='Enter age' 
                        type='number' 
                        fullWidth required 
                        value={age} 
                        onChange={(e) => setAge(e.target.value)}
                        error={error.age}
                        helperText={error.age ? "Age is required" : ""}
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
