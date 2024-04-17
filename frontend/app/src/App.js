import './App.css';
import ThermostatData from './Thermostat_Component';
import ClimatePage from './Components/ClimatePage/ClimatePage';

function App() {
  return (
    <div className="App">
      <ThermostatData />
    </div>
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
