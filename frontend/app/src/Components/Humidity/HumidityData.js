import React from 'react';
import { Card, CardContent, Typography, CircularProgress } from '../../MUI_imports';

export default function HumidityData({ humidityData, isLoading }) {
    // Destructure humidityData object
    let { humidity, average } = humidityData;

    if (isLoading) {
        return (
            <Card variant="outlined">
                <CardContent style={{ display: 'flex', justifyContent: 'center', alignItems: 'center', height: '150px' }}>
                    <CircularProgress />
                </CardContent>
            </Card>
        );
    }

    return (
        <Card variant="outlined">
            <CardContent>
                <Typography variant="h4" component="h2">
                    Humidity Data
                </Typography>
                <Typography variant="body1">
                    Current Humidity: {humidity}%
                </Typography>
                <Typography variant="body1" style={{ marginTop: '8px' }}>
                    Average Humidity: {average.toFixed(2)}%
                </Typography>
                <Typography variant="body1" style={{ marginTop: '8px' }}>
                    Preferred Humidity: 40% - 60%
                </Typography>
            </CardContent>
        </Card>
    );
}