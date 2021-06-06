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
//#include <car/Tachometr/Tachometr.h>
#include <car/Config/Config.h>
#include <IMU.h>

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

//        controller->getChassis()->setValue2(a, b);
        controller->getChassis()->setGazDiffValues(a, b);
    }
};
Config cfg;
TachometrConfig tachometrConfig;
CommunicatorConfig communicatorConfig;
ChassisConfig chassisConfig;
ControlConfig controlConfig;
IMU* mpu;
int gas = 50;

struct Ctrl {
    long int val_;
    long int prev_val_;
    long int t_;
} control{0,0};

void pidStep();

void setup(){
    communicatorConfig = {17, 'K', true, 57600};
    tachometrConfig = {8, 0.8, 15, 6, 0.8, 20};
    chassisConfig = {10};
    controlConfig = {0.05, 0.5, 0, 3, (long int)10e6, 0};
    cfg = {&communicatorConfig, &tachometrConfig, &chassisConfig, &controlConfig};

    Log = Log ? Log : new Logger();
    controller = controller ? controller : new Controller();
    pinMode(13, OUTPUT);

    control.t_ = micros();
    control.val_ = 0;
    control.prev_val_ = 0;

    mpu = new IMU(IMU::getDefaultConfig());
    if (mpu->init()) {
        while(true) {
            Log->println('e', "Cannot init IMU");
            delay(2000);
        }
    }

    controller->getCommunicator()->addListener('K', new ListenerWrapper([](Message& msg){
        String s = String((const char*)msg.getLoad());
        int divider = s.indexOf(' ');
        String paramName = s.substring(0, divider);
        String paramValue = s.substring(divider+1);
        cfg.update(&paramName, paramValue.c_str());
        Message msgAns;
        msgAns.setLoad(("Cfg " + paramName + ": ", paramValue).c_str());
        controller->getCommunicator()->send(msgAns);
    }));

    controller->getCommunicator()->addListener('L', new PingListener());

     controller->getCommunicator()->addListener('M', new MovementListener());

     // Reset
     controller->getCommunicator()->addListener('R', new ListenerWrapper([](Message& msg){
        control.val_ = 0;
     }));

     controller->os.addTask([]() {
         controller->getCommunicator()->read(true);
     }, 1);

//    controller->os.addTask([]() {
////        TachoData data = controller->getTachometr()->getData(false);
//
//        TachoData data1 = controller->tachometer[0]->getData(false);
//        TachoData data2 = controller->tachometer[1]->getData(false);
//
////        Log->println('_', data1.v, data2.v, data1.a, data2.a);
////        float v1 = data1.v, v2 = data2.v;
////        float e1 = target - v1, e2 = target - v2;
////        I[0] += e1; I[1] += e2;
////        float contr1 = e1 * 1 + I[0]*0.05, contr2 = e2*1 + I[1]*0.05;
////        signal[0] += contr1;
////        signal[1] += contr2;
////        controller->chassis->setValue2(signal[0], signal[1]);
//    }, 2);

    controller->os.addTask([](){
       pidStep();
    }, 1);
}

void pidStep() {
    auto c = controlConfig;

    auto data = mpu->read();
    long int t = micros();
    long int target = -1*c.wFactor * controller->getChassis()->_diff;
    long int err = target - (data.g.z - 6);

//    auto integr = control.val_ + 3.0*err*(t-control.t_)/10e6;
    auto integr = control.val_ + c.errIntegrAddFactor*err*(t-control.t_)/c.timeIntegrDivider;

    float df = 1.0*c.timeIntegrDivider*(err - control.prev_val_)/(t - control.t_);
//    const float Kp = 0.05, Ki = 0.5;

    int U = c.Kp * err + c.Ki * integr + c.Kd * df;
    control.t_ = t;
    control.val_ = integr;
    control.prev_val_ = err;

    if (controller->getChassis()->_gaz < 0) {
        U *= -1;
    }

    auto values = controller->getChassis()->getDifferential(controller->getChassis()->_gaz, U);
//    auto values = controller->getChassis()->getDifferential(controller->getChassis()->_gaz, U * (1 + 3*1.0/max(controller->getChassis()->_gaz, 1)));
    controller->getChassis()->setValue2(values.L, values.R);

//    if (micros() - i > 10000) {
//        i = micros();
////        Log->println('d', control.val_, " ", err);
//    }
//    Log->println(' ', control.val_, " ", err);
    char val[30];
    long int gyro = data.g.z;
    sprintf(val, "%d %ld %ld %ld %d %d",
        U, err, control.val_, gyro, controller->getChassis()->_gaz, controller->getChassis()->_diff
    );
    Message msg = Message('O', val);
    controller->getCommunicator()->send(msg);

}

void loop() {
#ifdef UNIT_TEST
    if (--iteratons) { return; }
#endif

//    pidStep();

}
