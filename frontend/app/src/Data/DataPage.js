import { Grid } from '@mui/material';
import ThermostatDataWrapper from '../Components/Thermostat/ThermostatDataWrapper.js';
import HumidityDataWrapper from '../Components/Humidity/HumidityDataWrapper.js';
import CO2Wrapper from '../Components/CO2/CO2Wrapper.js';
import SensorDataGraph from '../Components/DataHistory/SensorDataGraph.js';

export default function ClimatePage() {
  return (
    <Grid container spacing={3}>
      <Grid item xs={12} sm={6} md={4}>
        <ThermostatDataWrapper/>
      </Grid>
      <Grid item xs={12} sm={6} md={4}>
        <CO2Wrapper/>
      </Grid>
      <Grid item xs={12} sm={6} md={4}>
        <HumidityDataWrapper />
      </Grid>
      <Grid item xs={12}>
        <SensorDataGraph />
      </Grid>
    </Grid>
  );
}