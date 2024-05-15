import React from 'react';
import { Card, CardContent, Typography, CircularProgress } from '../../MUI_imports';

export default function ThermostatData({ thermData, isLoading }) {
  if (isLoading) {
    return (
      <Card>
        <CardContent style={{ display: 'flex', justifyContent: 'center', alignItems: 'center', height: '150px' }}>
          <CircularProgress />
        </CardContent>
      </Card>
    );
  }

  return (
    <Card>
      <CardContent>
        <Typography variant="h5" component="h2">
          Thermostat Data
        </Typography>
        <Typography color="textSecondary">
          Temperature: {thermData.temperature}
        </Typography>
      </CardContent>
    </Card>
  );
}