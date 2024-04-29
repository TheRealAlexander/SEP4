import '../../App.css';
import React, { useState, useEffect } from 'react';

export default function ThermostatData() {
     const [thermostatInfo, setThermostatInfo] = useState({
          temperature: 0
     });

     const [isLoading, setIsLoading] = useState(true);

     useEffect(() => {
          const interval = setInterval(() => {
              fetch('http://localhost:5200/getenvironmentData')
                  .then(response => response.json())
                  .then(data => {
                      let temperatureValue = data[0].temperature;
                      setThermostatInfo({ temperature: temperatureValue });
                  })
                  .catch(error => console.error('Error:', error));
                  setIsLoading(false);
          }, 5000);

          return () => clearInterval(interval);
      }, []);

     if (isLoading) {
          return <div>Loading...</div>;
     }

     return (
          <div>
               <h1>Thermostat Data</h1>
               <p>Temperature: {thermostatInfo.temperature}</p>
          </div>
     );
}