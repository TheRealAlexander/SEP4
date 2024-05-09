# Interface Contract

## Overview

This document outlines the interface contract between the Frontend and Backend
systems for the specific requirement stated below:

## **Requirement:**

As an admin, I would like to be able to see the indoor climate, temperature,
humidity, and CO2 concentration of the hall over time, to ensure the health of
the players and make it comfortable for the players.

## Requests for Environmental Data

### Request: Get Environmental Data

**Description:** This request is utilized to retrieve environmental data such as
indoor climate, temperature, humidity, and CO2 concentration over a period of
time.

**Method:** GET

**Parameters:**

- Integer 'hall_id'

**Response:**

- Status Code: 200 OK
- Body: JSON object containing environmental data.
-
- Double 'temperature' - average across 1 minute.
- Double 'humidity' - average across 1 minute.
- Double 'co2_concentration' - average across 1 minute.

**Example Response:**

```json
{
  "hall_id": "1234",
  "data": [
    {
      "timestamp": "2024-04-10T12:00:00Z",
      "temperature": 22.5,
      "humidity": 50,
      "co2_concentration": 800
    }
  ]
}
```


## Request for Users

### Request: Get Users By Role

**Description:** This request is used to retrieve a list of all users, 
seperated into multiple lists, one for each type of user, ie. Admin, 
Super and standard.

**Method:** Get

**Parameters:**
None

**Response:** 

- Status Code: 200 OK
- Body: JSON object containing lists of different types of users.

**Example Response:**

```json
{
  "AdminUsers": [
    {"Id": 1, "username": "Bob"},
    {"Id": 2, "username": "Alice"},
    //other admin users
  ],
  "SuperUsers": [
    {"Id": 3, "username": "Jens"},
    {"Id": 4, "username": "Luu"},
    //other super users
  ],
  "StandardUsers": [
    {"Id": 5, "username": "Emil"},
    {"Id": 6, "username": "Johan"},
    //other standard users
  ]
}
```


### Request: Change Permission of Users

**Description:** This request is used to change the user type of a 
list of users, namely SuperUsers and StandardUsers.

**Method:** UPDATE

**Parameters:**

List of Users

**Response:**

- Status Code: 200 OK
- body: JSON object containing an updated list of users - see:
  Get Users By Role.

**Example Response:**

See: Get Users By Role