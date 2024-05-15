FROM mcr.microsoft.com/dotnet/aspnet:7.0 AS base
WORKDIR /app
EXPOSE 5202

ENV ASPNETCORE_URLS=http://+:5202

RUN adduser -u 5678 --disabled-password --gecos "" appuser && chown -R appuser /app
USER appuser

FROM --platform=$BUILDPLATFORM mcr.microsoft.com/dotnet/sdk:7.0 AS build
ARG configuration=Release
WORKDIR /src
COPY ["backend/broker/Broker.csproj", "backend/broker/"]
RUN dotnet restore "backend/broker/Broker.csproj"
COPY . .
COPY ["backend/SharedObjects/Models", "/src/backend/SharedObjects/Models"]
RUN chmod -R 755 /src/backend/SharedObjects
WORKDIR "/src/backend/broker"
RUN dotnet build "Broker.csproj" -c $configuration -o /app/build

FROM build AS publish
ARG configuration=Release
RUN dotnet publish "Broker.csproj" -c $configuration -o /app/publish /p:UseAppHost=false

FROM base AS final
WORKDIR /app
COPY --from=publish /app/publish .
ENTRYPOINT ["dotnet", "Broker.dll"]