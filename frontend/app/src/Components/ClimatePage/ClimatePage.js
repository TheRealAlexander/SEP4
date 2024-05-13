import styles from './ClimatePage.module.css';
import '../Humidity/HumidityData.js';
import '../Thermostat/ThermostatData.js';
import ThermostatDataWrapper from '../Thermostat/ThermostatDataWrapper.js';
import HumidityDataWrapper from '../Humidity/HumidityDataWrapper.js';


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
                <CO2Component co2_concentration={data.co2_concentration}/>
            </div>
            <div className={styles.gridItem}>
                <HumidityDataWrapper />
            </div>
        </div>
    )
}

function CO2Component( {co2_concentration} ) {
    return (
        <div>
            <h1>CO2 Concentration</h1>
            <div>
                <h2>Current CO2 Concentration: {co2_concentration} ppm</h2>
            </div>
        </div>
    )
}