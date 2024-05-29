import React from 'react';
import HumidityDataWrapper from '../Components/Humidity/HumidityDataWrapper';
import { Card, Typography, Box } from '../MUI_imports';
import ThermostatDataWrapper from '../Components/Thermostat/ThermostatDataWrapper';

function CurrentConditions({ temperature, humidity }) {
    return (
        <Card sx={{ padding: 3, margin: 2, width: 300 }}>
            <Typography variant="h6" sx={{ textAlign: 'center' }}>Current Conditions</Typography>
            <Box sx={{ marginTop: 2 }}>
                <ThermostatDataWrapper/>
                <HumidityDataWrapper/>
            </Box>
        </Card>
    );
}

export default CurrentConditions;
