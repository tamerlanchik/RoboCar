//slave
// #define DEBUG

#include <Arduino.h>
#include "car/Controller/Controller.h"
#include "modules/Logger/Logger.h"
#include <modules/Communicator/Message.h>
#include <modules/Communicator/Listener.h>
#include <modules/Communicator/Communicator.h>
// #define UNIT_TEST
#ifdef UNIT_TEST
#include <leOS2Mock/leOS2Mock.h>
#include <modules/Communicator/SerialCommunicator.h>
typedef leOS2Mock leOS2;
#else
#include <leOS2.h>
#endif
#include <car/Tachometr/Tachometr.h>
#include <car/Config/Config.h>

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
Config cfg;
TachometrConfig tachometrConfig;
CommunicatorConfig communicatorConfig;
ChassisConfig chassisConfig;
//int signal[2] = {0,0};
float target = 5;
float I[2] = {0, 0};

int gas = 50;

void setup(){
    communicatorConfig = {17, 'K', true, 57600};
    tachometrConfig = {8, 0.8, 15, 6, 0.8, 20};
    chassisConfig = {10};
    cfg = {&communicatorConfig, &tachometrConfig, &chassisConfig};

    Log = Log ? Log : new Logger();
    controller = controller ? controller : new Controller();
    pinMode(13, OUTPUT);
    controller->getCommunicator()->addListener('K', new ListenerWrapper([](Message& msg){
        String s = String((const char*)msg.getLoad());
        int divider = s.indexOf(' ');
        String paramName = s.substring(0, divider);
        String paramValue = s.substring(divider+1);
        cfg.update(&paramName, paramValue.c_str());
//        if (paramName == "t.a") {
//            tachometrConfig.a = atof(paramValue.c_str());
////            Log->println('d', tachometrConfig.a);
//        } else if(paramName == "t.win") {
//            tachometrConfig.winSize = atoi(paramValue.c_str());
////            Log->println('d', tachometrConfig.winSize);
//        }
    }));

    controller->getCommunicator()->addListener('L', new PingListener());

    controller->getCommunicator()->addListener('N', new ListenerWrapper([](Message& msg){
        String s = String((const char*)msg.getLoad());
        target = atof(s.c_str());
    }));

     controller->getCommunicator()->addListener('M', new MovementListener());

     controller->os.addTask([]() {
         controller->getCommunicator()->read(true);
     }, 1);

    controller->os.addTask([]() {
//        TachoData data = controller->getTachometr()->getData(false);
        TachoData data1 = controller->tachometer[0]->getData(false);
        TachoData data2 = controller->tachometer[1]->getData(false);
        Log->println('_', data1.v, data2.v, data1.a, data2.a);
//        float v1 = data1.v, v2 = data2.v;
//        float e1 = target - v1, e2 = target - v2;
//        I[0] += e1; I[1] += e2;
//        float contr1 = e1 * 1 + I[0]*0.05, contr2 = e2*1 + I[1]*0.05;
//        signal[0] += contr1;
//        signal[1] += contr2;
//        controller->chassis->setValue2(signal[0], signal[1]);
    }, 2);


    controller->os.addTask([]() {
        struct Data { int gas; float speed; unsigned long tests; unsigned long changeTime; };
        static Data L{0, 0, 0, 0}, R{0, 0, 0, 0};

        static unsigned long last = 0;

        if (L.gas > 255 || R.gas > 255) {
//            Log->println('d', "End");
            return;
        }
        if (millis() - L.changeTime > 5000) {
            L.speed /= L.tests; L.tests = 0;
            R.speed /= R.tests; R.tests = 0;
            Log->println('_', L.gas, L.speed, R.speed);
            L.gas += 5; R.gas = L.gas;
            L.changeTime = millis();
            R.changeTime = L.changeTime;
        }
        TachoData l = controller->tachometer[0]->getData(true);
        TachoData r = controller->tachometer[1]->getData(true);
        if (millis() - last > 5) {
            last = millis();
            L.speed += l.v; L.tests++;
            R.speed += r.v; R.tests++;
        }
    }, 1);
}


void loop() {
#ifdef UNIT_TEST
    if (--iteratons) { return; }
#endif
}
