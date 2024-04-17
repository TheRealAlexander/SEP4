import './App.css';
import React, { useState, useEffect } from 'react';

function ThermostatData() {
     const [thermostatInfo, setThermostatInfo] = useState({
          temperature: 0
     });

     const [isLoading, setIsLoading] = useState(true);

     const fetchThermostatData = async () => {
          // THIS IS A SIMULATED API CALL!!!
          // CHANGE FOR REAL CALL UPON BACKEND IMPLEMENTATION
          return new Promise(resolve => {
               setTimeout(() => {
                    resolve({
                         temperature: 72
                    });
               }, 500);
          })
     }

     // UNCOMMENT THIS CODE WHEN BACKEND IS IMPLEMENTED
/*      const fetchThermostatData = async () => {
          try {
               const response = await fetch('',
                    {
                         method: 'GET',
                         headers: {
                              'Content-Type': 'application/json'
                         }
                    });
               
               if (!response.ok) {
                    throw new Error('HTTP error! status:&{response.status}');
               }

               const data = await response.json();
               return data;
          } catch (error) {
               console.error('Error:', error);
               return null;
          }
     } */

     useEffect(() => {
          fetchThermostatData().then(data => {
               setThermostatInfo(data);
               setIsLoading(false);
          });
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

export default ThermostatData;