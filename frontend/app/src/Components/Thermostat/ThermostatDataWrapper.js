import React from 'react';
import ThermostatData from './ThermostatData';
import { useSensorData } from '../../Services/ClimateService';

export default function ThermostatDataWrapper() {
  let { thermData, isLoading } = useSensorData();
  
  return <ThermostatData thermData={thermData} isLoading={isLoading} />;
}