FROM mcr.microsoft.com/dotnet/aspnet:7.0 AS base
WORKDIR /src
EXPOSE 5201

ENV ASPNETCORE_URLS=http://+:5201

# Copy everything and build the project.
COPY . ./
RUN dotnet restore
RUN dotnet publish -c Release -o out

# Build runtime image
FROM mcr.microsoft.com/dotnet/aspnet:7.0
WORKDIR /app
COPY --from=build-env /app/out .
ENTRYPOINT ["dotnet", "broker.dll"]