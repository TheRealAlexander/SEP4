import './App.css';
import { BrowserRouter as Router, Route, Routes } from 'react-router-dom';
import ThermostatData from './Components/Thermostat/ThermostatData';
import ClimatePage from './Components/ClimatePage/ClimatePage';
import HumidityComponent from './Components/Humidity/HumidityData';

function App() {
  return (
    <Router>
      <div className='App'>
        <Routes>
          <Route path="/" element={<ClimatePage data={data} />} />
          <Route path="/thermostat" element={<ThermostatData />} />
          <Route path="/humidity" element={<HumidityComponent />} />
        </Routes>
      </div>
    </Router>
  );
}

let data = {
  time: "12:00",
  location: "Living Room",
  temperature: 19,
  humidity: 50,
  co2_concentration: 800,
}


export default App;
