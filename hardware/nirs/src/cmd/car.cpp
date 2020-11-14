//slave
// #define DEBUG

#include <Arduino.h>
#include "car/Controller/Controller.h"
#include "modules/Logger/Logger.hpp"
#include <modules/Communicator/Message.h>
#include <modules/Communicator/Listener.h>
// #define UNIT_TEST
#ifdef UNIT_TEST
#include <leOS2Mock/leOS2Mock.h>
typedef leOS2Mock leOS2;
#else
#include <leOS2.h>
#endif

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
leOS2 os;

struct MovementListener : public Listener {
    void Handle(Message& msg) {
        String s = String((const char*)msg.getLoad());
        int divider = s.indexOf(' ');
        String a_s = s.substring(0, divider);
        String b_s = s.substring(divider+1);
        int a = atoi(a_s.c_str());
        int b = atoi(b_s.c_str());

        controller->getChassis()->setValue2(a, b);
    }
};
void setup(){
    os.begin();
    Log = Log ? Log : new Logger();
    controller = controller ? controller : new Controller();
    pinMode(13, OUTPUT);
    controller->getCommunicator()->addListener('L', new PingListener());
    controller->getCommunicator()->addListener('K', new MovementListener());
    os.addTask([]() {
        controller->getCommunicator()->read(true);
    }, 1);
}


void loop() {
//    digitalWrite(13, 1);
//    delay(500);
//    digitalWrite(13, 0);
//    delay(500);
//    Log->println('d', "AAd", 134);
//    Message msg = Message('M', "Hello fucking world!");
//    controller->getCommunicator()->send(msg);
//    controller->getCommunicator()->read(true);

#ifdef UNIT_TEST
    if (--iteratons) { return; }
#endif
}