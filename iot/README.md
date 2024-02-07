# IoT Project for ATmega2560

## Project Structure

- **`/src`**: Contains the source code files for the main application. The entry point is `main.c`, which demonstrates a simple LED blink program.
- **`/tests`**: Contains test code files. Currently, tests are placeholders and serve as an example of how to structure tests.
- **`Makefile`**: Defines rules for compiling the project, including building the main application and tests.

## Getting Started

### Prerequisites

To build and test this project, you will need:

- AVR-GCC toolchain for compiling AVR code.
- GNU Make for running build commands defined in the `Makefile`.
- An ATmega2560 microcontroller or compatible board for deploying and testing the firmware.

### Building the Project

To compile the main application, navigate to the `/iot` directory and run:

```bash
make build
```

This command compiles the source code in the `/src` directory and generates a `.hex` file suitable for flashing to an ATmega2560 microcontroller.

### Running Tests

To compile and run the tests, use the following command:

```bash
make test
```

Note: The current test setup is a placeholder and does not perform any actual tests. It's intended to demonstrate how tests could be structured and executed.

## Continuous Integration

This project uses GitHub Actions for continuous integration. The CI pipeline is triggered on pull requests and commits to the main branch. It compiles the main application and runs tests automatically. The results are reported directly in the pull request comments.