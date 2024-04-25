FROM mcr.microsoft.com/dotnet/aspnet:8.0 AS base
WORKDIR /app
EXPOSE 5000

ENV ASPNETCORE_URLS=http://+:5000

USER app
FROM --platform=$BUILDPLATFORM mcr.microsoft.com/dotnet/sdk:8.0 AS build
ARG configuration=Release
WORKDIR /src
COPY ["backend/microservices/autorisering/WebApi/WebApi.csproj", "backend/microservices/autorisering/WebApi/"]
RUN dotnet restore "backend/microservices/autorisering/WebApi/WebApi.csproj"
COPY . .
WORKDIR "/src/backend/microservices/autorisering/WebApi"
RUN dotnet build "WebApi.csproj" -c $configuration -o /app/build

FROM build AS publish
ARG configuration=Release
RUN dotnet publish "WebApi.csproj" -c $configuration -o /app/publish /p:UseAppHost=false

FROM base AS final
WORKDIR /app
COPY --from=publish /app/publish .
ENTRYPOINT ["dotnet", "WebApi.dll"]
