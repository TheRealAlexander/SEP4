import styles from './ClimatePage.module.css';
import '../Humidity/HumidityData.js';
import '../Thermostat/ThermostatData.js';
import ThermostatDataWrapper from '../Thermostat/ThermostatDataWrapper.js';
import HumidityDataWrapper from '../Humidity/HumidityDataWrapper.js';
import CO2Wrapper from '../CO2/CO2Wrapper.js';


export default function ClimatePage( {data} ) {
    return (
        <div className={styles.container}>
            <div className={styles.header}>
                <h1> Location: {data.location} </h1>
                <h1> Time: {data.time} </h1>
            </div>
            
            <div className={styles.gridItem}>
                <ThermostatDataWrapper/>
            </div>
            <div className={styles.gridItem}>
                <CO2Wrapper/>
            </div>
            <div className={styles.gridItem}>
                <HumidityDataWrapper />
            </div>
        </div>
    )
}