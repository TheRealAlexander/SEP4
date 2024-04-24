# Fake arduino

`fake_arduino.c` kan bruges til at simulere det HTTP request, som Arduino'en vil sende til backend. 

## Build
Linux: 
```
$ gcc fake_arduino.c -o fake_arduino
```

Windows:
```
> cl fake_arduino.c
```

## Usage
Simulere request hver 15-ende sekund
```
./fake_arduino simulate myhostname.com 80
```

Sende en POST request
```
./fake_arduino single-request myhostname.com 80 /my/endpoint mybody.json
```
