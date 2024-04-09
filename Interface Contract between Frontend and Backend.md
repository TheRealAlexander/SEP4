# Interface Contract

## Overview

This document provides detailed information about the interface between Frontend
& Backend.

## Requests for an object and its details

### Request: Get User

**Description:** This request is used to retrieve information about a specific
user.

**Method:** GET

**Parameters:**

- `userId` (required): The unique identifier of the user.

**Response:**

- Status Code: 200 OK
- Body: JSON object representing the user details.

**Example:** { "name": "John Doe", "age": 25, "email": "johndoe@example.com" }
