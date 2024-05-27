# Interface Contract

## Overview

This document outlines the interface contract between the Frontend and Backend
systems for the specific requirement stated below:

## **Requirement:**

As an admin, I would like to be able to see the indoor climate, temperature,
humidity, and CO2 concentration of the hall over time, to ensure the health of
the players and make it comfortable for the players.

## Requests for Environmental Data

### Request: Get Environmental Data By Hall ID

**Description:** This request is utilized to retrieve environmental data such as
indoor climate, temperature, humidity, and CO2 concentration over a period of
time.

**Method:** GET

**Parameters:**

- Integer 'hall_id'

**Response:**

- Status Code: 200 OK
- Body: JSON object containing environmental data.
- Double 'temperature' - average across 1 minute.
- Double 'humidity' - average across 1 minute.
- Double 'co2_concentration' - average across 1 minute.

**Response Example:**

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

### Request: Get Environmental Data With Limit

**Description** This request is utilized to retrieve environmental data with a
limit to how many data entries there should be retrieved.

**Method** GET

**Parameters:**

- Integer 'hall_id'
- Integer 'limit'

**Response:**

- Status Code: 200 OK
- Body: JSON object containing environmental data.

- Double 'temperature' - average across 1 minute.
- Double 'humidity' - average across 1 minute.
- Double 'co2_concentration' - average across 1 minute.

**Response Example:**

```json
{
  "data": [
    {
      "timestamp": "2024-04-10T12:00:00Z",
      "temperature": 22.5,
      "humidity": 50,
      "co2_concentration": 800
    },
    //and more data entries
  ]
}
```

### Request: Get Environmental Data by Date interval

**Description** This request is utilized to retrieve environmental data between
two dates

**Method:** GET

**Parameters:**

- Integer: 'HallID'
- DateTime 'dateTime1'
- DateTime 'dateTime2'

**Response:**

- Status Code: 200 OK
- Body: JSON object containing a list of environmental data objects.

- Double 'temperature' - average across 1 minute.
- Double 'humidity' - average across 1 minute.
- Double 'co2_concentration' - average across 1 minute.

**Response Example:**

```json
  {
    "data1": [
      {
        "timestamp": "2024-04-10T12:00:00Z",
        "temperature": 22.5,
        "humidity": 50,
        "co2_concentration": 800
      }
    ],
    "data2": [
      {
        "timestamp": "2024-04-10T12:01:00Z",
        "temperature": 24,
        "humidity": 45,
        "co2_concentration": 790
      }
    ]
  }
```

## **Requirement:**

Som admin vil jeg gerne have, at hallens indeklima kan justeres automatisk, for
at styrke helbredet af spillerne.

## Requests for setting preferred climate settings:

### Request: Get preferred climate settings for each hall

**Description**

This request will be utilized to fetch the current preferred climate settings
for each hall.

**Method:** GET

**Parameters:**

- NONE

**Response:**

- Status Code: 200 OK
- Body: JSON object containing a list of all halls and their respective current
  preferred climate settings.

**Response Example:**

```json
  {
    "Hall1": [
      {
        "HallID" : 1,
        "Temperature" : 21,
        "Humidity" : 40,
        "CO2_Concentration" : 800
      }
    ],
    "Hall2": [
      {
        "HallID" : 2,
        "Temperature" : 21,
        "Humidity" : 40,
        "CO2_Concentration" : 800
      }
    ]
  }
```

### Request: Post preferred climate settings for specific hall

**Description**

This request will be utilized to set the preferred climate settings for a
specific hall

**Method:** POST

- URL: /PostEnvironmentDataGoal
- Port : 5200

**Parameters:**

- Integer: 'HallID'
- Double: 'desiredTemperature'
- Double: 'desiredHumidity'
- Integer: 'desiredCO2'

**Response:**

- Status Code: 200 OK
- Json body which confirms that the posted data corresponds with what the user
  expects to have posted

**Example Reponse:**

```json
    {
      "HallID" : 1,
      "desiredTemperature" : 21,
      "desiredHumidity" : 40,
      "desiredCO2" : 800
    }
```

### Request: User registration

**Description:**

This section of the interface contract describes the user-registration 
functionality provided by the Frontend system. It allows users to register
a new account on the platform, which can be used to login to the system.

**Method:** POST

- URL: Register
- Port: 5001

**Parameters:**

Body: A JSON object containing user information.

- username: The user's username.
- password: The user's password.
- e-mail: The user's e-mail.
- age: the user's age.

**Request Example:**

```json
{
    "username": "user",
    "password": "pass",
    "e-mail": "email@domain.com",
    "age": 00
}
```
**Successful Response:**

- Status Code: 200 OK

**Error Response Example:**

```json
HTTP/1.1 400 Bad Request
Content-Type: text/plain; charset=utf-8
Date: Wed, 08 May 2024 09:25:58 GMT
Server: Kestrel
Transfer-Encoding: chunked

"Something went wrong"
```

## Request: User Login

**Description:**

This section of the interface contract describes the login functionality
provided by the Backend system. It allows users to authenticate and receive a
token that can be used for subsequent authenticated requests.

**Method:** POST

- URL: Auth/login
- Port: 5001

**Parameters:**

Body: A JSON object containing user login credentials.

- username: The user's username.
- password: The user's password.

**Request Example:**

```json
{
  "username": "user",
  "password": "securepassword123"
}
```

**Successful Response:**

- Status Code: 200 OK
- Body: A string containing the JWT.

**Response Example:**

```json
{
  eyJhbGciOiJIUzUxMiIsInR5cCI6IkpXVCJ9.eyJzdWIiOiJKV1RTZXJ2aWNlQWNjZXNzVG9rZW4iLCJqdGkiOiI2NDUxZWJkMi1jMWZjLTRkMmEtYmFmYS0yM2RmMmU5MmY5MmMiLCJpYXQiOiIwNS8wOC8yMDI0IDA5OjI0OjQ1IiwiaHR0cDovL3NjaGVtYXMueG1sc29hcC5vcmcvd3MvMjAwNS8wNS9pZGVudGl0eS9jbGFpbXMvbmFtZSI6IkVtaWwiLCJodHRwOi8vc2NoZW1hcy5taWNyb3NvZnQuY29tL3dzLzIwMDgvMDYvaWRlbnRpdHkvY2xhaW1zL3JvbGUiOiJTdXBlclVzZXIiLCJFbWFpbCI6InRlc3RAdmlhdWMuZGsiLCJBZ2UiOiIyMyIsImV4cCI6MTcxNTE2Mzg4NSwiaXNzIjoiSldUQXV0aGVudGljYXRpb25TZXJ2ZXIiLCJhdWQiOiJKV1RTZXJ2aWNlQmxhem9yV2FzbUNsaWVudCJ9.RDVWDzDZxYnmxfCTtU-7rHQN3ABDWWB8FdCzBck7M8j1UO45PxSxPfEmScPTg9b2SV1IxD--KpyOBeVNabuVpA
}
```

**Error Response Example:**

```json
HTTP/1.1 400 Bad Request
Content-Type: text/plain; charset=utf-8
Date: Wed, 08 May 2024 09:25:58 GMT
Server: Kestrel
Transfer-Encoding: chunked

Username is incorrect. (or "Password is incorrect.")
```

## Request: Get All Users

**Description:** This endpoint retrieves all registered users from the system,
categorizing them into three separate lists based on their roles: Admins,
SuperUsers, and Users.

**Method:** GET

- URL: /GetAllUsers
- Port: 5001

**Parameters:** None

Successful Response:

- Status Code: 200 OK
- Body: A JSON object containing three arrays of users, each corresponding to a
  specific user role.

**Response Example:**

```json
[
  [],
  [
    {
      "username": "Emil",
      "password": "1234",
      "email": "test@viauc.dk",
      "role": "SuperUser",
      "age": 23
    }
  ],
  [
    {
      "username": "Johan",
      "password": "12343434",
      "email": "testasd@viauc.dk",
      "role": "User",
      "age": 23
    },
    {
      "username": "Luu",
      "password": "12343sada434",
      "email": "tesasdtasd@viauc.dk",
      "role": "User",
      "age": 25
    },
    {
      "username": "Santa",
      "password": "dfghjka434",
      "email": "test4@viauc.dk",
      "role": "User",
      "age": 27
    }
  ]
]
// This example returns an empty admins list.
```

**Failed Response:**

- Status Code: 500 Internal Server Error
- Body: A JSON object containing an error message indicating an issue with
  retrieving user data.

**Error Response Example:**

```json
Error retrieving data from the database.
```

## **Requirement:**

Som admin vil jeg gerne kunne give rettigheder til udvalgte brugere, så de kan
styre indeklima eller oprette turneringer.

## Request: Swap Roles

**Description:** This endpoint accepts a list of users and swaps their roles:
"SuperUser" becomes "User" and vice versa. This is particularly useful in
scenarios where role adjustments are needed en masse, such as during
organizational restructuring or access rights reassignment.

**Method:** POST

- URL: /User/swapRoles
- Port: 5001

**Parameters:**

- **Body:** A JSON array containing user objects. Each user object must include
  at least the username and the current role.

**Request Example:**

```json
[
  {
    "username": "Johan",
    "password": "12343434",
    "email": "testasd@viauc.dk",
    "role": "SuperUser",
    "age": 23
  },
  {
    "username": "Emil",
    "password": "1234",
    "email": "test@viauc.dk",
    "role": "User",
    "age": 23
  }
]
```

**Successful Response:**

- **Status Code:** 200 OK
- **Body:** A JSON array of users with their roles swapped.

**Response Example:**

```json
[
  {
    "username": "Johan",
    "password": "12343434",
    "email": "testasd@viauc.dk",
    "role": "User",
    "age": 23
  },
  {
    "username": "Emil",
    "password": "1234",
    "email": "test@viauc.dk",
    "role": "SuperUser",
    "age": 23
  }
]
```

**Failed Response (Empty users list):**

- **Status Code:** 400 Bad Request
- **Body:** A JSON object containing an error message indicating that no users
  were provided.

**Failed Request Example:**

```json
[

]
```

**Failed Response Example:**

```json
No users provided.
```

**Failed Response (Invalid role provided):**

- **Status Code:** 400 Bad Request
- **Body:** A JSON object containing an error message indicating that invalid
  roles have been provided.

**Failed Request Example:**

```json
[
{
      "username": "Santa",
      "password": "dfghjka434",
      "email": "test4@viauc.dk",
      "role": "",
      "age": 27
}
]
```

**Failed Response Example:**

```json
Role must be either User or SuperUser!
```

# Som admin vil jeg gerne kunne oprette en turnering i det ønskede format, så jeg har de bedste forudsætninger for at få afviklet denne. #72

## Overview
The `handleSubmit` function in the `TournamentFormDialog` component is responsible for validating the form inputs, creating the tournament data object, sending it to the backend service `CreateTournament`, and handling the response. It uses state variables to manage the form data and error messages.

## Sent Data
When the form is submitted, the following data is sent to the backend:

### Tournament Data Object
- **Name**: `string`
  - **Description**: The name of the tournament.
  - **Source**: `nameOfTournament` state variable.

- **DateAndTime**: `DateTime`
  - **Description**: The date and time of the tournament in `datetime-local` format.
  - **Source**: `dateAndTime` state variable.

- **Description**: `string`
  - **Description**: A brief description of the tournament.
  - **Source**: `description` state variable.

- **FieldCount**: `Integer`
  - **Description**: The number of fields for the tournament.
  - **Source**: `baneAntal` state variable.

- **Format**: `string`
  - **Description**: The format of the tournament. Possible values are "Americano" and "Mexicano".
  - **Source**: `format` state variable.

- **Participants**: `Empty Array`
  - **Description**: An array of participants. Initially, this is an empty array.
  - **Source**: Static value `[]`.

- **State**: `Integer`
  - **Description**: The state of the tournament. This is set to `1` initially.
                     Ranges as follows: 1 = Planned, 2 = Ongoing, 3 = Finished
  - **Source**: Static value `1`.

- **tournamentID**: `string`
  - **Description**: The tournament ID. This should be assigned by the backend.
  - **Source**: Static value `""`.

### Example JSON Payload
```json
{
  "Name": "Tournament Name Example",
  "DateAndTime": "2023-12-31T12:00",
  "Description": "This is a description of the tournament.",
  "FieldCount": 4,
  "Format": "Americano",
  "Participants": [],
  "State": 1,
  "tournamentID": ""
}
```

  - **Success Response Example (Status Code 200)**
```json
{
  "message": "Tournament created successfully!",
  "tournamentID": "12345"  // Example ID assigned by the backend
}
```

  - **Error Response Example (Status Code other than 200)**
```json
{
  "message": "Error creating tournament" // Example message
}
```

# handleSaveEdits Function Documentation

## Description
The `handleSaveEdits` function updates a tournament's details by sending the modified tournament data to the backend service. It displays appropriate feedback messages based on the operation's success or failure.

## Parameters
- **updatedTournament**: `object`
  - **Description**: The tournament object containing updated details.
  - **Properties**:
    - `Name`: `string`
    - `DateAndTime`: `DateTime`
    - `Description`: `string`
    - `FieldCount`: `integer`
    - `Format`: `string`
    - `Participants`: `String[]`
    - `State`: `integer`
    - `tournamentID`: `string`

## Sent Data Example
```json
{
  "Name": "Updated Tournament Name",
  "DateAndTime": "2024-05-31T12:00",
  "Description": "Updated description of the tournament.",
  "FieldCount": 5,
  "Format": "Mexicano",
  "Participants": ["Participant1", "Participant2"],
  "State": 2,
  "tournamentID": "12345"
}
```

  - **Success Response Example (Status Code 200)**
```json
{
  "message": "Tournament updated successfully!",
  "tournamentID": "12345"  // tournamentID should match the sent tournamentID
}
```

  - **Error Response Example (Status Code other than 200)**
```json
{
  "message": "Error saving new tournament data" // Example message
}
```


### handleDeleteTournament Function Documentation

## Description
The `handleDeleteTournament` function deletes a tournament by sending a delete request to the backend service. It displays appropriate feedback messages based on the operation's success or failure.

## Parameters
- **tournamentID**: `string`
  - **Description**: The ID of the tournament to be deleted.

## Sent Data Example
No data body is sent, only the tournament ID is used in the endpoint URL.

## Expected Response
### Success Response
- **Status Code**: `200`
- **Body**:
```json
  {
    "message": "Tournament deleted successfully!"
  }
```


### handleRegister Function Documentation

## Description
The `handleRegister` function registers a participant for a tournament by sending the participant's name to the backend service. It displays appropriate feedback messages based on the operation's success or failure.

## Parameters
None (uses `participantName` state and `tournament.id`)

## Sent Data Example
```json
{
  "tournamentID": "12345",
  "participantName": "John Doe"
}
```

  - **Success Response Example (Status Code 200)**
```json
{
  "message": "Participant added successfully!"
}
```

  - **Error Response Example (Status Code other than 200)**
```json
{
  "message": "Error adding participant!" // Example message
}
```
