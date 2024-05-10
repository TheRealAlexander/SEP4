import React, { useState, useEffect } from 'react';
import { Typography, Slider, Paper, Box } from '@mui/material';

function TemperatureHumidityControl({ initialTemperature, initialHumidity, onTemperatureChange, onHumidityChange }) {
    const [temperature, setTemperature] = useState(initialTemperature);
    const [humidity, setHumidity] = useState(initialHumidity);

    // Update internal state when props change
    useEffect(() => {
        setTemperature(initialTemperature);
        setHumidity(initialHumidity);
    }, [initialTemperature, initialHumidity]);

    return (
        <Paper sx={{ padding: 3, margin: 2 }}>
            <Typography variant="h6">Admin</Typography>
            <Box sx={{ marginTop: 2 }}>
                <Typography gutterBottom>Temperature ({temperature}°C)</Typography>
                <Slider
                    value={temperature}
                    onChange={(e, newValue) => {
                        setTemperature(newValue);
                        onTemperatureChange(newValue);
                    }}
                    aria-labelledby="temperature-slider"
                    valueLabelDisplay="auto"
                    min={10}
                    max={40}
                />
            </Box>
            <Box sx={{ marginTop: 2 }}>
                <Typography gutterBottom>Humidity ({humidity}%)</Typography>
                <Slider
                    value={humidity}
                    onChange={(e, newValue) => {
                        setHumidity(newValue);
                        onHumidityChange(newValue);
                    }}
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