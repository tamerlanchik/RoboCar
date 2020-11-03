//base
#define DEBUG
#include <Arduino.h>
#include <car/Controller/Controller.h>
//#include <car/pins/pins.h>
#include <modules/config/config.h>
#include <modules/Log/Log.hpp>
Log* log;
Controller* controller;

void setup()
{
  log = new log();
  #if defined DEBUG
    log->d("BASE");
  #endif
  controller = new Controller();
}

void loop()
{
  /*manager->checkRadioConnection(10);
  delay(2);
  manager->sendTestLongParcelRadio();
  delay(100);*/
//  controller->retranslateSerialToRadio();
  delay(1);
}
