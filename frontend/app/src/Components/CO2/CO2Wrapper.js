import React from 'react';
import CO2Component from './CO2Comp';
import { useSensorData } from '../../Services/ClimateService';

export default function HumidityDataWrapper() {
    let { CO2Data, isLoading } = useSensorData();

    return <CO2Component humidityData={CO2Data} isLoading={isLoading} />;
}