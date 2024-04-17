import './App.css';
import { BrowserRouter as Router, Route, Routes } from 'react-router-dom';
import ThermostatData from './Thermostat_Component';
import ClimatePage from './Components/ClimatePage/ClimatePage';

function App() {
  return (
    <Router>
      <div className='App'>
        <Routes>
          <Route path="/" element={<ClimatePage data={data} />} />
          <Route path="/thermostat" element={ThermostatData} />
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
