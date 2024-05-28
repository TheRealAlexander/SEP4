import axios from 'axios';
import { useState, useEffect } from 'react';

const API_BASE_URL = '/Broker';

export function useSensorData() {
  const [thermData, setThermData] = useState({ temperature: 0 });
  const [humidityData, setHumidityData] = useState({
    humidity: 0,
    readings: [],
    average: 0,
  });
  const [CO2Data, setCO2Data] = useState({ CO2: 0 });
  const [isLoading, setIsLoading] = useState(true);

  useEffect(() => {
    const fetchData = async () => {
      try {
        const response = await axios.get(`${API_BASE_URL}/GetSensorData/1`);
        console.log('response:', response);
        const data = response.data;
        
        // Update thermostat data
        let temperatureValue = data[data.length - 1]?.temperature || 0;
        setThermData({ temperature: temperatureValue });
        
        // Update humidity data
        const humidityValue = data[data.length - 1]?.humidity || 0;
        setHumidityData((prevData) => {
          const newReadings = [...prevData.readings, humidityValue];
          const newAverage = newReadings.reduce((a, b) => a + b, 0) / newReadings.length;

          return {
            humidity: humidityValue,
            readings: newReadings.length > 10 ? newReadings.slice(1) : newReadings,
            average: newAverage,
          };
        });

        // Update CO2 data
        const CO2Value = data[data.length - 1]?.CO2 || 0;
        setCO2Data({ CO2: CO2Value });

        setIsLoading(false);
      } catch (error) {
        console.error('Error fetching data:', error);
        // Set default values on error
        setThermData({ temperature: 'Network might be down!' });
        setHumidityData({ humidity: 0, readings: [], average: 0 });
        setCO2Data({ CO2: 0 });
        setIsLoading(false);
      }
    };

    const interval = setInterval(fetchData, 5000);
    fetchData(); // Fetch immediately when component mounts

    return () => clearInterval(interval);
  }, []);

  return { thermData, humidityData, CO2Data, isLoading };
}


export async function getLimitedSensorData(limit) {
  try {
    const response = await axios.get(`${API_BASE_URL}/GetSensorData?limit=${limit}`);
    return response.data;
  } catch (error) {
    console.error(error);
  }
}

export async function setPreferredValue(HallID, desiredTemperature, desiredHumidity) {
  try {
    const data = {
      HallID,
      desiredTemperature,
      desiredHumidity
      // Add CO2 value here if needed
    };

    const response = await axios.post(`${API_BASE_URL}/setPreferredValue`, data);
    return response.data;
  } catch (error) {
    console.error('Error setting preferred values:', error);
    throw error; // Re-throwing error to handle it in the component
  }
}

