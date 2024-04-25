import React, { useState, useEffect } from 'react';

export default function HumidityData() {
    const [humidity, setHumidity] = useState(0.0);
    const [readings, setReadings] = useState([]);

    useEffect(() => {
        const interval = setInterval(() => {
            fetch('http://localhost:5200/getenvironmentData')
                .then(response => response.json())
                .then(data => {
                    const humidityValue = data.humidity; // Access the humidity property
                    setHumidity(humidityValue.toFixed(2));
    
                    // Add the new reading to the array and keep only the last 10 readings
                    setReadings((prevReadings) => {
                        const newReadings = [...prevReadings, humidityValue];
                        return newReadings.length > 10 ? newReadings.slice(1) : newReadings;
                    });
                })
                .catch(error => console.error('Error:', error));
        }, 5000);
    
        return () => clearInterval(interval);
    }, []);

    // Calculate the average of the last 10 readings
    const average = readings.reduce((a, b) => a + b, 0) / readings.length;

    const style = {
        display: 'flex',
        flexDirection: 'column',
        justifyContent: 'center',
        alignItems: 'center',
        height: 'auto',
        width: 'auto',
        padding: '2em',
        backgroundColor: '#f0f0f0',
        borderRadius: '10px',
        boxShadow: '0px 10px 20px rgba(0, 0, 0, 0.25)',
        fontSize: '20px',
        color: '#333',
        fontFamily: '"Roboto", "Helvetica", "Arial", sans-serif'
    };

    return (
        <div style={style}>
            <div>Current Humidity: {humidity}%</div>
            <br></br>
            <div>Average Humidity: {average.toFixed(2)}%</div>
            <br></br>
            <div>Prefered Humidity: 40% - 60%</div>
        </div>
    );
}