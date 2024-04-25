FROM mcr.microsoft.com/devcontainers/dotnet:1-8.0-bookworm

# Update package lists and install psql
RUN apt-get update && apt-get install -y postgresql-client

# Install maven 
RUN apt-get update && apt-get install -y maven

# Install java 17 
RUN apt-get update && apt-get install -y openjdk-17-jdk

# Install MongoDB tools directly
RUN apt-get update && apt-get install -y wget \
    && wget https://fastdl.mongodb.org/tools/db/mongodb-database-tools-debian10-x86_64-100.5.1.tgz \
    && tar -xvzf mongodb-database-tools-debian10-x86_64-100.5.1.tgz -C /usr/local/bin --strip-components=1 \
    && rm -f mongodb-database-tools-debian10-x86_64-100.5.1.tgz







# [Optional] Uncomment this section to install additional OS packages.
# RUN apt-get update && export DEBIAN_FRONTEND=noninteractive \
#     && apt-get -y install --no-install-recommends <your-package-list-here>

# [Optional] Uncomment this line to install global node packages.
# RUN su vscode -c "source /usr/local/share/nvm/nvm.sh && npm install -g <your-package-here>" 2>&1