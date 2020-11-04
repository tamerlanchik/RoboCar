//slave
// #define DEBUG

#include <Arduino.h>
#include "car/Controller/Controller.h"
#include "modules/Logger/Logger.hpp"

bool state = 1;
int iteratons = 1;
class PingListener : public Listener {
public:
    void Handle(Message& msg) {
        digitalWrite(13, state);
        state = !state;
    }
};

Controller* controller;
long long t=0;
Logger* Log;
void setup(){
    Log = new Logger();
    controller = new Controller();
    pinMode(13, OUTPUT);
    controller->getCommunicator()->addListener('L', new PingListener());
}


void loop() {
//    digitalWrite(13, 1);
//    delay(500);
//    digitalWrite(13, 0);
//    delay(500);
//    Log->println('d', "AAd", 134);
//    Message msg = Message('M', "Hello fucking world!");
//    controller->getCommunicator()->send(msg);
    controller->getCommunicator()->read(true);

#ifdef UNIT_TEST
    if (--iteratons) { return; }
#endif
}