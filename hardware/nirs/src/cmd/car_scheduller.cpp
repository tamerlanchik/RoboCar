//slave
// #define DEBUG

#include <Arduino.h>
#ifdef UNIT_TEST
#include <leOS2Mock/leOS2Mock.h>
typedef leOS2Mock leOS2;
#else
#include <leOS2.h>
#endif
#include <Arduino.h>
#include "car/Controller/Controller.h"
#include "modules/Logger/Logger.h"


bool state = 1;
int iteratons = 1;

leOS2 os;

class PingListener : public Listener {
public:
    void Handle(Message& msg) {
        digitalWrite(13, state);
        state = !state;
    }
};
Controller* controller;
Logger* Log;
void setup(){
    Log = new Logger();
    controller = new Controller();
    pinMode(13, OUTPUT);
    os.begin();
    controller->getCommunicator()->addListener('L', new PingListener());

    os.addTask([](){
        controller->getCommunicator()->read(true);
    }, os.convertMs(32));   // кратно 16
}


void loop() {
#ifdef UNIT_TEST
    if (--iteratons) { return; }
#endif
}