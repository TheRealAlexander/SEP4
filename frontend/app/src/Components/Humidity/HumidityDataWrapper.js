import React from 'react';
import HumidityData from './HumidityData';
import { useHumidityData } from '../../Services/ClimateService';

export default function HumidityDataWrapper() {
    let { humidityData, isLoading } = useHumidityData();

    return <HumidityData humidityData={humidityData} isLoading={isLoading} />;
}