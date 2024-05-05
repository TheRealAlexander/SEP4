import axios from 'axios';
import { useState, useEffect } from 'react';

const API_BASE_URL = 'http://localhost:5200';

const useThermostatData = () => {
  const [thermData, setThermData] = useState({ temperature: 0 });
  const [isLoading, setIsLoading] = useState(true);

  useEffect(() => {
    const fetchData = async () => {
      try {
        const response = await axios.get(`${API_BASE_URL}/getenvironmentData`);
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

export default useThermostatData;
