#include "wifi.h"
#include "driverMHZ19B.h"
#include <util/delay.h>
#include <stdio.h>
#include <string.h>
#include <Arduino.h>
int main(){
 WHZ19B_init();
    while(1) {
        WHZ19B_readCO2();
    } 
}
