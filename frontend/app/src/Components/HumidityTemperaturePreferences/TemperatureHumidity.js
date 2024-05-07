import React from 'react';
import { Typography, Slider, Paper, Box } from '@mui/material';

function TemperatureHumidityControl({ initialTemperature, initialHumidity, onTemperatureChange, onHumidityChange }) {
    return (
        <Paper sx={{ padding: 3, margin: 2 }}>
            <Typography variant="h6">Temperature and Humidity Control</Typography>
            <Box sx={{ marginTop: 2 }}>
                <Typography gutterBottom>Temperature ({initialTemperature}°C)</Typography>
                <Slider
                    value={initialTemperature}
                    onChange={(e, newValue) => onTemperatureChange(newValue)}
                    aria-labelledby="temperature-slider"
                    valueLabelDisplay="auto"
                    min={10}
                    max={40}
                />
            </Box>
            <Box sx={{ marginTop: 2 }}>
                <Typography gutterBottom>Humidity ({initialHumidity}%)</Typography>
                <Slider
                    value={initialHumidity}
                    onChange={(e, newValue) => onHumidityChange(newValue)}
                    aria-labelledby="humidity-slider"
                    valueLabelDisplay="auto"
                    min={30}
                    max={70}
                />
            </Box>
        </Paper>
    );
}

export default TemperatureHumidityControl;
