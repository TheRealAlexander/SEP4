import React, { useState } from "react";
import { Line } from "react-chartjs-2";
import { getLimitedSensorData } from "../../Services/ClimateService.js";
import TextField from "@mui/material/TextField";
import Button from "@mui/material/Button";
import {
  Chart,
  CategoryScale,
  LinearScale,
  PointElement,
  LineElement,
} from "chart.js";
import Box from "@mui/material/Box";
import Snackbar from "@mui/material/Snackbar";
import Alert from "@mui/material/Alert";
import Typography from "@mui/material/Typography";

Chart.register(PointElement, LineElement, CategoryScale, LinearScale);

function SensorDataGraph() {
  const [count, setCount] = useState(10); // Default value
  const [sensorData, setSensorData] = useState([]);
  const [error, setError] = useState(null);
  const [open, setOpen] = useState(false);

  const fetchData = async () => {
    try {
      let data = await getLimitedSensorData(count);
      console.log(data); // Keep this line if you want to continue logging the data
      setSensorData(data.value || []); // Use data.value instead of data
    } catch (err) {
      setError(err.message);
      setOpen(true);
      setSensorData([]); // Set sensorData to an empty array when an error occurs
    }
  };

  const options = {
    scales: {
      xAxes: [
        {
          type: "time",
          time: {
            parser: "HH:mm:ss",
            tooltipFormat: "HH:mm:ss",
            unit: "second",
            unitStepSize: 5,
            displayFormats: {
              millisecond: "HH:mm:ss",
              second: "HH:mm:ss",
              minute: "HH:mm:ss",
              hour: "HH:mm:ss",
              day: "HH:mm:ss",
              week: "HH:mm:ss",
              month: "HH:mm:ss",
              quarter: "HH:mm:ss",
              year: "HH:mm:ss",
            },
          },
          distribution: "linear",
          ticks: {
            autoSkip: false, // This will show all labels
            maxRotation: 90, // This will rotate labels to prevent overlap
            minRotation: 90, // This will rotate labels to prevent overlap
            callback: function (value, index, values) {
              return new Date(value).toLocaleTimeString(); // Format the value to time string
            },
          },
        },
      ],
      yAxes: [
        {
          ticks: {
            beginAtZero: true,
          },
        },
      ],
    },
    plugins: {
      title: {
        display: true,
        text: "Temperature over Time",
      },
    },
  };

  const humidityOptions = {
    ...options,
    plugins: {
      title: {
        display: true,
        text: "Humidity over Time",
      },
    },
  };

  const CO2Options = {
    ...options,
    plugins: {
      title: {
        display: true,
        text: "CO2 Levels over Time",
      },
    },
  };

  const labels = sensorData.map((item) =>
    new Date(item.temperatureTimestamp).toLocaleString()
  );

  const temperatureData = {
    labels: labels,
    datasets: [
      {
        label: "Temperature",
        data: sensorData.map((item) => item.temperature || 0),
        fill: false,
        backgroundColor: "rgb(255, 99, 132)",
        borderColor: "rgba(255, 99, 132, 0.2)",
      },
    ],
  };

  const humidityData = {
    labels: labels,
    datasets: [
      {
        label: "Humidity",
        data: sensorData.map((item) => item.humidity || 0),
        fill: false,
        backgroundColor: "rgb(75, 192, 192)",
        borderColor: "rgba(75, 192, 192, 0.2)",
      },
    ],
  };

  const CO2Data = {
    labels: labels,
    datasets: [
      {
        label: "CO2",
        data: sensorData.map((item) => item.cO2 || 0),
        fill: false,
        backgroundColor: "rgb(255, 205, 86)",
        borderColor: "rgba(255, 205, 86, 0.2)",
      },
    ],
  };

  const handleClose = (event, reason) => {
    if (reason === "clickaway") {
      return;
    }

    setOpen(false);
  };

  return (
    <Box>
      <TextField
        type="number"
        value={count}
        onChange={(e) => setCount(e.target.value)}
        label="Number of readings"
        variant="outlined"
      />
      <Button onClick={fetchData} variant="contained">
        Fetch
      </Button>
      <Typography variant="h6">Temperature over Time</Typography>
      <Box
        sx={{
          height: { xs: "300px", sm: "500px" },
          width: { xs: "100%", sm: "100%" },
        }}
      >
        <Line data={temperatureData} options={options} />
      </Box>
      <Typography variant="h6">Humidity over Time</Typography>
      <Box
        sx={{
          height: { xs: "300px", sm: "500px" },
          width: { xs: "100%", sm: "100%" },
        }}
      >
        <Line data={humidityData} options={humidityOptions} />
      </Box>
      <Typography variant="h6">CO2 Levels over Time</Typography>
      <Box
        sx={{
          height: { xs: "300px", sm: "500px" },
          width: { xs: "100%", sm: "100%" },
        }}
      >
        <Line data={CO2Data} options={CO2Options} />
      </Box>
      <Snackbar open={open} autoHideDuration={6000} onClose={handleClose}>
        <Alert onClose={handleClose} severity="error">
          {error}
        </Alert>
      </Snackbar>
    </Box>
  );
}

export default SensorDataGraph;
