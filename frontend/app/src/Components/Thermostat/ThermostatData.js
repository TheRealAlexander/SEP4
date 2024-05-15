import '../../App.css';
import React from 'react';

export default function ThermostatData({ thermData, isLoading }) {
  if (isLoading) {
    return <div>Loading...</div>;
  }

  return (
    <div>
      <h1>Thermostat Data</h1>
      <p>Temperature: {thermData.temperature}</p>
    </div>
  );
}