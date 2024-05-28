import React, { useState } from 'react';
import { Box, Card, CardActionArea, CardContent, Typography, Grid, Container, Button } from '@mui/material';
import TempHumiComp from './TempHumiComp';
import LightControlComp from './LightControlComp';
import CurrentConditionsComp from './CurrentConditionsComp';


function HomePage() {
    const [selectedHal, setSelectedHal] = useState(null);
    const [controlStates, setControlStates] = useState({
        'Hal 1': { temperature: 22, humidity: 50, lights: Array(4).fill(50) }, 
        'Hal 2': { temperature: 22, humidity: 50, lights: Array(5).fill(50) },
        'Hal 3': { temperature: 22, humidity: 50, lights: Array(7).fill(50) }, 
    });

    const [tempControlStates, setTempControlStates] = useState({ ...controlStates });

    const cardStyles = (isActive) => ({
        width: 300,
        height: 150,
        margin: 6,
        backgroundColor: isActive ? 'lightblue' : 'white',
        transition: '0.3s',
        '&:hover': {
            backgroundColor: 'lightblue',
            boxShadow: '0 8px 16px 0 rgba(0,0,0,0.2)'
        }
    });

    const handleSave = () => {
      setControlStates(tempControlStates);
  };

  const handleCancel = () => {
      setTempControlStates({ ...controlStates });
  };

  const updateTemperature = (hal, newValue) => {
      setTempControlStates(prev => ({
          ...prev,
          [hal]: { ...prev[hal], temperature: newValue }
      }));
  };

  const updateHumidity = (hal, newValue) => {
      setTempControlStates(prev => ({
          ...prev,
          [hal]: { ...prev[hal], humidity: newValue }
      }));
  };

  const updateLightIntensity = (hal, laneId, newValue) => {
      setTempControlStates(prev => ({
          ...prev,
          [hal]: {
              ...prev[hal], 
              lights: prev[hal].lights.map((intensity, index) => index === laneId - 1 ? newValue : intensity)
          }
      }));
    };

    return (
      <Container sx={{ paddingTop: '75px', minHeight: '100vh', overflowY: 'auto', paddingLeft: '64px',  marginLeft: '200px' }}>
          <Box sx={{ marginLeft: '32px' }}> 
              <Box sx={{ display: 'flex', flexDirection: 'row', justifyContent: 'center', marginBottom: 4 }}>
                  {['Hal 1', 'Hal 2', 'Hal 3'].map((hal, index) => (
                      <Card sx={{ width: 300, height: 150, margin: 6, backgroundColor: selectedHal === hal ? 'lightblue' : 'white', transition: '0.3s', '&:hover': { backgroundColor: 'lightblue', boxShadow: '0 8px 16px 0 rgba(0,0,0,0.2)' } }} key={index}>
                          <CardActionArea 
                              onClick={() => setSelectedHal(hal)}
                              sx={{
                                  height: '100%',
                                  width: '100%',
                                  display: 'flex',
                                  flexDirection: 'column',
                                  justifyContent: 'center'
                              }}
                          >
                              <CardContent>
                                  <Typography variant="h5" sx={{ textAlign: 'center' }}>{hal}</Typography>
                              </CardContent>
                          </CardActionArea>
                      </Card>
                  ))}
              </Box>
              {selectedHal && (
                  <Grid container spacing={2} justifyContent="flex-end">
                      <Grid item xs={4} sx={{ overflowY: 'auto', maxHeight: 500 }}>
                          <Box>
                              {tempControlStates[selectedHal].lights.map((intensity, index) => (
                                  <LightControlComp
                                      key={index}
                                      laneId={index + 1}
                                      initialIntensity={intensity}
                                      onIntensityChange={(newIntensity) => updateLightIntensity(selectedHal, index + 1, newIntensity)}
                                  />
                              ))}
                          </Box>
                      </Grid>
                      <Grid item xs={4}>
                          <TempHumiComp 
                              initialTemperature={tempControlStates[selectedHal].temperature}
                              initialHumidity={tempControlStates[selectedHal].humidity}
                              onTemperatureChange={(newValue) => updateTemperature(selectedHal, newValue)}
                              onHumidityChange={(newValue) => updateHumidity(selectedHal, newValue)}
                          />
                      </Grid>
                      <Grid item xs={4}>
                          <CurrentConditionsComp 
                              temperature={tempControlStates[selectedHal].temperature}
                              humidity={tempControlStates[selectedHal].humidity}
                          />
                          <Button onClick={handleSave} variant="contained" color="primary" sx={{ margin: 1 }}>Save Changes</Button>
                          <Button onClick={handleCancel} variant="outlined" color="secondary" sx={{ margin: 1 }}>Cancel</Button>
                      </Grid>
                  </Grid>
              )}
          </Box>
      </Container>
    );
}
export default HomePage;