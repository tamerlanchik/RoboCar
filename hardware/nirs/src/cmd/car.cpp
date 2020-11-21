//slave
// #define DEBUG

#include <Arduino.h>
#include "car/Controller/Controller.h"
#include "modules/Logger/Logger.hpp"
#include <modules/Communicator/Message.h>
#include <modules/Communicator/Listener.h>
#include <modules/Communicator/Communicator.h>
// #define UNIT_TEST
#ifdef UNIT_TEST
#include <leOS2Mock/leOS2Mock.h>
#include <car/Tachometr/Tachometr.h>
#include <modules/Communicator/SerialCommunicator.h>

typedef leOS2Mock leOS2;
#else
#include <leOS2.h>
#include <car/Tachometr/Tachometr.h>

#endif

//class TestProgram : public Controller {
//public:
//    TestProgram() : Controller() {}
//    void run();
//    leOS2 os;
//    void setup();
//
//public:
//    void handleMovementMessage(Message& msg) {
//        String s = String((const char*)msg.getLoad());
//        int divider = s.indexOf(' ');
//        String a_s = s.substring(0, divider);
//        String b_s = s.substring(divider+1);
//        int a = atoi(a_s.c_str());
//        int b = atoi(b_s.c_str());
//        chassis->setValue2(a, b);
//    }
//};

//class PingListener : public Listener {
//public:
//    void Handle(Message& msg) = TestProgram::handleMovementMessage;
//};

Controller* controller;
Logger* Log;
int iteratons = 1;

class PingListener : public Listener {
    bool state = 1;
public:
    void operator()(Message& msg) {
        digitalWrite(13, state);
        state = !state;
    }
};

struct MovementListener : public Listener {
    void operator()(Message& msg) {
        String s = String((const char*)msg.getLoad());
        int divider = s.indexOf(' ');
        String a_s = s.substring(0, divider);
        String b_s = s.substring(divider+1);
        int a = atoi(a_s.c_str());
        int b = atoi(b_s.c_str());

        controller->getChassis()->setValue2(a, b);
    }
};

//void TestProgram::setup() {
//    os.begin();
//    Log = Log ? Log : new Logger();
//
////    os.addTask([]() {
////        TachoData data = controller->getTachometr()->getData();
////        Log->println('d', "Data: ", data.x, data.v);
////    }, 30);
////    Communicator* c = new SerialCommunicator(1, 1, 1, Mode::TEXT);
//
//    comm->addListener('L', new ListenerWrapper([](Message& msg){
//
//    }));
//
//}

//void TestProgram::run() {
//    setup();
//    while(1);
//}
void setup(){
//    TestProgram().run();
    Log = Log ? Log : new Logger();
    controller = controller ? controller : new Controller();
    pinMode(13, OUTPUT);
     controller->getCommunicator()->addListener('L', new PingListener());
     controller->getCommunicator()->addListener('K', new MovementListener());
     controller->os.addTask([]() {
         controller->getCommunicator()->read(true);
     }, 1);

//    controller->os.addTask([]() {
//        TachoData data = controller->getTachometr()->getData();
//        Log->println('_', data.x, data.v);
//    }, 30);
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


//D: Start calc: currX= 112 19236 412
//D: 0 100
//D: iter:  560 19236 392 108
//D: 560 -100
//D: iter:  560 19163 56 104
//0.11 5600.00
//
//
//D: Start calc: currX= 132 19804 724
//D: 0 100
//D: iter:  660 19804 704 128
//D: 660 -100
//D: iter:  -140 19804 688 124
//0.13 -1400.00
//D: Start calc: currX= 132 19804 724
//D: 0 100
//D: iter:  660 19804 704 128
//D: 660 -100
//D: iter:  -140 19804 688 124
//0.13 -1400.00