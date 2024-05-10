import React from 'react';
import { Card, Typography, Box } from '@mui/material';

function CurrentConditions({ temperature, humidity }) {
    return (
        <Card sx={{ padding: 3, margin: 2, width: 300 }}>
            <Typography variant="h6" sx={{ textAlign: 'center' }}>Current Conditions</Typography>
            <Box sx={{ marginTop: 2 }}>
                <Typography>Temperature: {temperature}°C</Typography>
                <Typography>Humidity: {humidity}%</Typography>
            </Box>
        </Card>
    );
}

export default CurrentConditions;
