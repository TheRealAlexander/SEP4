import axios from 'axios';
import { useState, useEffect } from 'react';

const API_BASE_URL = 'http://localhost:5200';

export function useThermostatData() {
  const [thermData, setThermData] = useState({ temperature: 0 });
  const [isLoading, setIsLoading] = useState(true);

  useEffect(() => {
    const fetchData = async () => {
      try {
        const response = await axios.get(`${API_BASE_URL}/GetEnvironmentData`);
        const data = response.data;

        let temperatureValue = data[0]?.temperature; // Use optional chaining to handle undefined

        if (temperatureValue === undefined) {
          // Set a default value if temperature is undefined or null
          temperatureValue = 0;
          setIsLoading(false);
        }
        setThermData({ temperature: temperatureValue });
        setIsLoading(false);
        console.log('Updated thermData:', { temperature: temperatureValue });

      } catch (error) {
        console.error('Error fetching data:', error);
        // Remove once backend is implemented
            setThermData({ temperature: 'CatchBlock activated, network might be down!' });
               setIsLoading(false);
      }
    };
    // Remove comment to fetch data every 5 seconds
    // const interval = setInterval(fetchData, 5000);
    fetchData(); // Fetch immediately when component mounts

     // Remove comment to clear interval when component unmounts
     //return () => clearInterval(interval);
  }, []);

  return { thermData, isLoading };
};


export function useHumidityData() {
  const [humidityData, setHumidityData] = useState({
      humidity: 0,
      readings: [],
      average: 0
  });
  const [isLoading, setIsLoading] = useState(true);

  useEffect(() => {
      const fetchData = async () => {
          try {
              const response = await axios.get(`${API_BASE_URL}/GetEnvironmentData`);
              const data = response.data;
              const humidityValue = data[0].humidity;

              setHumidityData(prevData => {
                  const newReadings = [...prevData.readings, humidityValue];
                  const newAverage = newReadings.reduce((a, b) => a + b, 0) / newReadings.length;

                  return {
                      humidity: humidityValue,
                      readings: newReadings.length > 10 ? newReadings.slice(1) : newReadings,
                      average: newAverage
                  };
              });

              setIsLoading(false);
          } catch (error) {
              console.error('Error fetching data:', error);
              // Remove once backend is implemented
              setHumidityData({
                  humidity: 'CatchBlock activated, network might be down!',
                  readings: [],
                  average: 0
              });
              setIsLoading(false);
          }
      };

      // Remove comment to fetch data every 5 seconds
      //const interval = setInterval(fetchData, 5000);
      fetchData(); // Fetch immediately when component mounts

      // Remove comment to clear interval when component unmounts
      //return () => clearInterval(interval);
  }, []);

  return { humidityData, isLoading };
};
