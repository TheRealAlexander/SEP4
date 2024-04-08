# Uses the node:18-alpine image as base image
FROM node:18-alpine

# Set the working directory to /sep4frontend/
WORKDIR /sep4frontend/

# Copy the current directory contents into the container at /sep4frontend/
COPY public/ /sep4frontend/public
COPY src/ /sep4frontend/src
COPY package.json /sep4frontend/

# Install any needed packages specified in package.json
RUN npm install

# Make port 3000 available to the world outside this container and start the app
CMD ["npm", "start"]