# Development Container Documentation

## Overview
This development container is designed to streamline the development process for projects. It provides a consistent and isolated environment where developers can build, test, and debug their applications without worrying about setting up dependencies or dealing with compatibility issues. The container is configured using a `devcontainer.json` file and a `docker-compose.yml` file, both of which define the environment settings and services required for development.

## Contents
1. **Services**: The container consists of three main services:
   - **app**: This service is the primary development environment where you'll work on your application. It's based on the `mcr.microsoft.com/devcontainers/dotnet:1-8.0-bookworm` image and includes additional tools such as `psql` (PostgreSQL client), `maven`, and `java 17`.
   - **db**: This service provides a PostgreSQL database server (version 14.3) for storing and managing your application data. It's configured with default credentials (`POSTGRES_USER: postgres`, `POSTGRES_PASSWORD: postgres`) and exposes port `5432`.
   - **rabbitmq**: This service provides a RabbitMQ message broker (version 3 with management plugin) for handling messaging within your application. It's configured with default credentials (`RABBITMQ_DEFAULT_USER: rabbitmq`, `RABBITMQ_DEFAULT_PASS: rabbitmq`) and exposes ports `5672` and `15672`.

2. **Port Forwarding**: The container forwards the following ports to the host machine, enabling access to various services:
   - `5000`: Default port for C# (.NET) applications.
   - `5001`: Default secure port for C# (.NET) applications.
   - `5432`: Default port for PostgreSQL database connections.
   - `8080`: Default port for HTTP connections (optional).
   - `5672`: Default port for RabbitMQ messaging.
   - `15672`: Default port for RabbitMQ management dashboard.

## Usage
1. **Setting up the Development Environment**:
   - Ensure Docker is installed on your system.
   - Clone the project repository containing the `devcontainer.json` and `docker-compose.yml` files.
   - Open the project folder in your preferred code editor (e.g., Visual Studio Code).
   - If prompted, allow the editor to reopen the project in a development container.

2. **Working with the Application**:
   - Develop your C# (.NET) application within the `app` service's workspace folder.
   - Utilize tools such as `dotnet`, `psql`, `maven`, and `java` for building, testing, and debugging your application.
   - Interact with the PostgreSQL database using `psql` or through your application's code.
   - Utilize RabbitMQ for message-based communication by connecting to `localhost:5672`.

3. **Managing Dependencies and Packages**:
   - Install additional dependencies or packages as needed using `dotnet`, `maven`, or other package managers available within the container.

## Additional Customizations
- You can uncomment and modify the optional sections in the `Dockerfile` to install additional OS packages or global Node.js packages as per your project requirements.

## Resources
- [devcontainer.json Format Details](https://aka.ms/devcontainer.json)
- [devcontainers/templates GitHub Repository](https://github.com/devcontainers/templates/tree/main/src/dotnet-postgres)

This documentation provides an overview of the development container's contents and usage instructions. For more detailed information, refer to the provided resources or consult the README file in the project repository.
