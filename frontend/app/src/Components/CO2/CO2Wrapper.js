import React from 'react';
import CO2Component from './CO2Comp';
import { useHumidityData } from '../../Services/ClimateService';

export default function HumidityDataWrapper() {
     // TEMP DATA:
     let CO2Data = {
          co2_concentration: 1000
     };

     // CHANGE TO USE CORRECT DATASERVICE!!!!!!!!!
    let { CO2Data_T, isLoading } = useHumidityData();

    return <CO2Component humidityData={CO2Data} isLoading={isLoading} />;
}