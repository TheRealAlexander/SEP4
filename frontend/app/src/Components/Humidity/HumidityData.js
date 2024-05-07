import React from 'react';

export default function HumidityData({ humidityData, isLoading }) {
    // Destructure humidityData object
    const { humidity, average } = humidityData;

    if (isLoading) {
        return <div>Loading...</div>;
    }

    return (
        <div>
            <h1>Humidity Data</h1>
            <div>Current Humidity: {humidity}%</div>
            <br />
            <div>Average Humidity: {average.toFixed(2)}%</div>
            <br />
            <div>Preferred Humidity: 40% - 60%</div>
        </div>
    );
}