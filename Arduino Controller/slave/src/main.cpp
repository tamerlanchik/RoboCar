//slave
#define DEBUG

#include <Arduino.h>
#include "Manager.h"
#include "pins.h"
#include "Logger.h"
Logger* Log;
Manager* manager;

void setup(){
  Log = new Logger();
  Log->d("CAR");
  manager = new Manager();
  delay(1000);
}


void loop()
{
  manager->testing();
}
