//slave
#define DEBUG

#include <Arduino.h>
#include "Manager.h"
#include "pins.h"
#include "Logger.h"
Logger* Log;
Manager* manager;
long long t=0;

void setup(){
  Log = new Logger();
  Log->d("CAR");
  Serial.println("BBegin");
  manager = new Manager();
  pinMode(9, OUTPUT);
  delay(1000);
}


void loop()
{
  manager->handleMessage(manager->getRadioMessage());
  if(millis()-t > 1000){
    Log->d("Im awake");
    t = millis();
  }
}
