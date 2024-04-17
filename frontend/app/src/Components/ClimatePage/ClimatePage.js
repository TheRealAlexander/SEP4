import styles from './ClimatePage.module.css';


export default function ClimatePage( {data} ) {
    return (
        <div className={styles.container}>
            <div className={styles.header}>
                <h1> Location: {data.location} </h1>
                <h1> Time: {data.time} </h1>
            </div>
            
            <div className={styles.gridItem}>
                <TemperatureComponent temperature={data.temperature}/>
            </div>
            <div className={styles.gridItem}>
                <CO2Component co2_concentration={data.co2_concentration}/>
            </div>
            <div className={styles.gridItem}>
                <HumidityComponent humidity={data.humidity}/>
            </div>
        </div>
    )
}

function TemperatureComponent( {temperature} ) {
    return (
        <div>
            <h1>Temperature</h1>
            <div>
                <h2>Current Temperature: {temperature} &deg;C</h2>
            </div>
        </div>
    )
}

function HumidityComponent( {humidity} ) {
    return (
        <div>
            <h1>Humidity</h1>
            <div>
                <h2>Current Humidity: {humidity}%</h2>
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