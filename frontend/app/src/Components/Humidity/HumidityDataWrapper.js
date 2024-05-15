import React from 'react';
import HumidityData from './HumidityData';
import { useHumidityData } from '../../Services/ClimateService';

export default function HumidityDataWrapper() {
    const { humidityData, isLoading } = useHumidityData();

    return <HumidityData humidityData={humidityData} isLoading={isLoading} />;
}