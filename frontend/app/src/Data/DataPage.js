import styles from './ClimatePage.module.css';
import '../Components/Humidity/HumidityData.js';
import '../Components/Thermostat/ThermostatData.js';
import ThermostatDataWrapper from '../Components/Thermostat/ThermostatDataWrapper.js';
import HumidityDataWrapper from '../Components/Humidity/HumidityDataWrapper.js';
import CO2Wrapper from '../Components/CO2/CO2Wrapper.js';


export default function ClimatePage( ) {
    return (
        <div className={styles.container}>
            <div className={styles.header}>

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