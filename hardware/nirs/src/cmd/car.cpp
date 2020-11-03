//slave
#define DEBUG

#include <Arduino.h>
#include "car/Controller/Controller.h"
#include "modules/Logger/Logger.h"
//#include <../modules/Logger/Logger.h>

Logger* Log;
Controller* controller;
long long t=0;

void setup(){
    t = millis();
    Log = new Logger();
    Log->d("CAR");
    controller = new Controller();
    pinMode(9, OUTPUT);
//    delay(1000);
}


void loop()
{
//    controller->handleMessage(controller->getRadioMessage());
    Log->d("Im awake");
    controller->ping(millis()-t);
    if(millis()-t > 1000){
        Log->d("Im awake");
        t = millis();
    }
#ifndef UNIT_TEST
    return;
#endif
}

#ifndef UNIT_TEST
int main() {
    setup();
    loop();
}
#endif