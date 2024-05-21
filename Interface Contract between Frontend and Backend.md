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

## Request: User registration

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



### Tournaments

## Get All Tournaments

**Method***: GET

**URL:** http://turnering_webapi:5101/tournaments

**Description:** Retrieves a list of all tournaments.

**Response:** 200 OK, returns a list of Tournament objects.

**Response example:**

```json
[
  {
    "TournamentID": "60d5ecb1747a80a41c8e6f32",
    "Name": "NameOfTournament",
    "State": 1,
    "TimeAndDate": "2022-12-12T14:30:00Z",
    "Description": "Tournament 1",
    "FieldCount": 5,
    "Format": "Single Elimination",
    "Participants": ["Participant1", "Participant2"]
  },
  {
    "TournamentID": "60d5ecb1747a80a41c8e6f33",
    "Name": "NameOfTournament",
    "State": 2,
    "TimeAndDate": "2023-01-01T09:00:00Z",
    "Description": "Tournament 2",
    "FieldCount": 8,
    "Format": "Double Elimination",
    "Participants": ["Participant3", "Participant4"]
  }
]
```

## Create Tournament

**Method:** POST

**URL:** http://turnering_webapi:5101/tournaments

**Description:** Creates a new tournament.

**Parameters:** A JSON object representing the tournament to be created in the request body.

**Request Example:**

```json
{
  "State": 1,
  "Name": "NameOfTournament",
  "TimeAndDate": "2022-12-12T14:30:00Z",
  "Description": "New Tournament",
  "FieldCount": 5,
  "Format": "Americano",
  "Participants": []
}
```

**Response:** 200 OK, returns the created Tournament object.

**Response Example:**

```json
{
  "TournamentID": "60d5ecb1747a80a41c8e6f34",
  "Name": "NameOfTournament",
  "State": 1,
  "TimeAndDate": "2022-12-12T14:30:00Z",
  "Description": "New Tournament",
  "FieldCount": 5,
  "Format": "Americano",
  "Participants": []
}
```

## Update Tournament

**Method:** PUT

**URL:** http://turnering_webapi:5101/tournaments/{tournamentID}

**Description:** Updates an existing tournament.

**Parameters:** tournamentID in the path. A JSON object representing the updated tournament data in the request body.

**Request Example:**

```json
{
  "TournamentID": "60d5ecb1747a80a41c8e6f34",
  "Name": "NameOfTournament",
  "TimeAndDate": "2023-01-01T09:00:00Z",
  "Description": "Updated Tournament",
  "FieldCount": 8,
  "Format": "Mexicano"
}
```

**Response:** 200 OK, returns the updated Tournament object.

**Response Example:**

```json
{
  "TournamentID": "60d5ecb1747a80a41c8e6f34",
  "State": 1,
  "Name": "NameOfTournament",
  "TimeAndDate": "2023-01-01T09:00:00Z",
  "Description": "Updated Tournament",
  "FieldCount": 8,
  "Format": "Mexicano",
  "Participants": ["Participant1", "Participant2"]
}
```

## Delete Tournament

**Method: DELETE**

**URL:** http://turnering_webapi:5101/tournaments/{tournamentID}

**Description:** Deletes an existing tournament.

**Parameters:** tournamentID in the path.

**Response:** 200 OK.

### Participants

## Add Participant to Tournament

**Method:** POST

**URL:** http://turnering_webapi:5101/tournaments/{tournamentID}/participants

**Description:** Adds a participant to an existing tournament.

**Parameters:** tournamentID in the path. A JSON object representing the participant to be added in the request body.

**Request Example:**

```json
{
  "TournamentID": "60d5ecb1747a80a41c8e6f34",  
  "name": "New Participant"
}
```

**Response:** 200 OK, returns the added Participant object.

**Response Example:**

```json
{
  "TournamentID": "60d5ecb1747a80a41c8e6f34",
  "name": "New Participant"
}
```

## Remove Participant from Tournament

**Method:** DELETE

**URL:** http://turnering_webapi:5101/tournaments/{tournamentID}/participants/{participant}

**Description:** Removes a participant from an existing tournament.

**Parameters:** tournamentID and participant in the path.

**Response:** 200 OK.
