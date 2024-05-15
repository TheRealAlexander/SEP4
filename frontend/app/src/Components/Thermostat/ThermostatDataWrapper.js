import React from 'react';
import ThermostatData from './ThermostatData';
import { useThermostatData } from '../../Services/ClimateService';

export default function ThermostatDataWrapper() {
  let { thermData, isLoading } = useThermostatData();
  
  return <ThermostatData thermData={thermData} isLoading={isLoading} />;
}