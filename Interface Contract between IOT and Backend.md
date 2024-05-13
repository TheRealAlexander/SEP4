# Interface Contract

## Overview

This document provides detailed information about the interface between IOT &
Backend.

## Request frequency is set by backend (CO2, Temperature,Humidity, Etc)

## Data type sent: JSON strings over HTTP

Example of a request sent from the IoT-device to the backend web service. The
request contains one or more measurements:

```json5
{
    "temperatures": 20.3,   // Unit: Celcius
    "temperature": 20.3,    // Unit: Celcius
    "humidity": 40.5,       // Unit: % volume
    "co2": 423              // Unit: ppm
}
```

The backend response can contain zero or more instructions for the IoT-device:

```json5
{
    "wantNextMeasurementDelay": 15, // Controls the number of seconds before the IoT-device sends the next measurements
    "recalibrateCO2": true          // Controls wether the CO2 sensor spend 20 minutes to recalibrate
    "openWindow": false     // If the response is empty, previous openWindow value is used
}
```
