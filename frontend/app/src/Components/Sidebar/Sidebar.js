import React, { useState } from 'react';
import { Box, Card, CardActionArea, CardContent, Typography } from '@mui/material';
import TemperatureHumidityControl from '../HumidityTemperaturePreferences/TemperatureHumidity';

function HomePage() {
    const [selectedHal, setSelectedHal] = useState(null);
    const [controlStates, setControlStates] = useState({
        'Hal 1': { temperature: 22, humidity: 50 },
        'Hal 2': { temperature: 22, humidity: 50 },
        'Hal 3': { temperature: 22, humidity: 50 }
    });

    const cardStyles = (isActive) => ({
        width: 300,
        height: 150,
        margin: 6,
        backgroundColor: isActive ? 'lightblue' : 'white',
        transition: '0.3s',
        '&:hover': {
            backgroundColor: 'lightblue',
            boxShadow: '0 8px 16px 0 rgba(0,0,0,0.2)'
        }
    });

    const updateTemperature = (hal, newValue) => {
        setControlStates(prev => ({
            ...prev,
            [hal]: { ...prev[hal], temperature: newValue }
        }));
    };

    const updateHumidity = (hal, newValue) => {
        setControlStates(prev => ({
            ...prev,
            [hal]: { ...prev[hal], humidity: newValue }
        }));
    };

    return (
        <Box sx={{
            display: 'flex',
            flexDirection: 'column',
            alignItems: 'center',
            justifyContent: 'flex-start',
            minHeight: '100vh',
            width: '100%'
        }}>
            <Box sx={{ display: 'flex', flexDirection: 'row' }}>
                {['Hal 1', 'Hal 2', 'Hal 3'].map((hal, index) => (
                    <Card sx={cardStyles(selectedHal === hal)} key={index}>
                        <CardActionArea 
                            onClick={() => setSelectedHal(hal)}
                            sx={{
                                height: '100%',
                                width: '100%',
                                display: 'flex',
                                flexDirection: 'column',
                                justifyContent: 'flex-start'
                            }}
                        >
                            <CardContent sx={{ flexGrow: 1, display: 'flex', alignItems: 'center', justifyContent: 'center' }}>
                                <Typography variant="h5" component="div" sx={{ textAlign: 'center' }}>
                                    {hal}
                                </Typography>
                            </CardContent>
                        </CardActionArea>
                    </Card>
                ))}
            </Box>
            {selectedHal && (
                <Box sx={{ marginTop: 4 }}>
                    <Typography variant="h4" sx={{ textAlign: 'center' }}>
                        Controls of {selectedHal}
                    </Typography>
                    <TemperatureHumidityControl 
                        initialTemperature={controlStates[selectedHal].temperature}
                        initialHumidity={controlStates[selectedHal].humidity}
                        onTemperatureChange={(newValue) => updateTemperature(selectedHal, newValue)}
                        onHumidityChange={(newValue) => updateHumidity(selectedHal, newValue)}
                    />
                </Box>
            )}
        </Box>
    );
}

export default HomePage;
