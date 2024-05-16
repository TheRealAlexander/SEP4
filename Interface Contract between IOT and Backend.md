# Interface Contract

## Overview

This document provides detailed information about the interface between IOT &
Backend.

## **Requirement:**
Som admin vil jeg gerne kunne indstille hallens indeklima manuelt, så jeg kan tilpasse det til spillernes behov.

### Request frequency is set by backend (CO2, Temperature, Humidity, Etc)

### Data type sent: JSON strings over HTTP

Example of a request sent from the IoT-device to the backend web service. The
request contains one or more measurements:

**Request Example:**
```json5
{
    "temperature": 20.3,    // Unit: Celcius
    "humidity": 40.5,       // Unit: % volume
    "co2": 423,              // Unit: ppm
    "hallId": 37            // Identifies the Arduino unit
}
```

The backend response can contain zero or more instructions for the IoT-device:

**Response Example:**
```json5
{
  "success": true,
  "code": 0,
  "hallId": 37,
  "openWindow": false
}
```
