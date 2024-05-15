import React from 'react';
import { Card, CardContent, Typography, CircularProgress } from '../../MUI_imports';

export default function CO2Component({ co2_concentration, isLoading }) {

     if (isLoading) {
          return (
              <Card>
                  <CardContent style={{ display: 'flex', justifyContent: 'center', alignItems: 'center', height: '150px' }}>
                      <CircularProgress />
                  </CardContent>
              </Card>
          );
      }

    return (
        <Card>
            <CardContent>
                <Typography variant="h5" component="div">
                    CO2 Concentration
                </Typography>
                <Typography variant="h6" color="text.secondary">
                    Current CO2 Concentration: {co2_concentration} ppm
                </Typography>
            </CardContent>
        </Card>
    );
}
