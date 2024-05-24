import React from 'react';
import HumidityData from './HumidityData';
import { useSensorData } from '../../Services/ClimateService';

export default function HumidityDataWrapper() {
    let { humidityData, isLoading } = useSensorData();

    return <HumidityData humidityData={humidityData} isLoading={isLoading} />;
}