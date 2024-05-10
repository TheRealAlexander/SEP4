import React from 'react';
import { Typography, Slider, Paper } from '@mui/material';

function LightControl({ laneId, initialIntensity, onIntensityChange }) {
    return (
        <Paper sx={{ padding: 3, margin: 2 }}>
            <Typography variant="h6">Lane {laneId} Light</Typography>
            <Slider
                value={initialIntensity}
                onChange={(e, newValue) => onIntensityChange(newValue)}
                aria-labelledby={`light-slider-lane-${laneId}`}
                valueLabelDisplay="auto"
                min={0}
                max={100}
                step={5}
            />
        </Paper>
    );
}

export default LightControl;
