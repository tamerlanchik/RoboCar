//base
#define DEBUG
#include <Arduino.h>
#include <Manager.h>
#include <pins.h>
#include <config.h>
Logger* Log;
Manager* manager;

void setup()
{
  Log = new Logger();
  #if defined DEBUG
    Log->d("BASE");
  #endif
  manager=new Manager();
}

void loop()
{
  /*manager->checkRadioConnection(10);
  delay(2);
  manager->sendTestLongParcelRadio();
  delay(100);*/
  manager->retranslateSerialToRadio();
  delay(1);
}
