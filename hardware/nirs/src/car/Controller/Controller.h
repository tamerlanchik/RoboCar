//
// Created by andrey on 03.11.2020.
//

#ifndef ROBOCAR_CONTROLLER_H
#define ROBOCAR_CONTROLLER_H

#ifdef UNIT_TEST
#include "modules/Logger/Logger.h"
#include "car/Chassis/Chassis.h"
#include <car/config.h>
#else
#include <Logger.h>
#include <Chassis.h>
#include <config.h>
#endif
#include <Arduino.h>
//#include <RadioExtended.h>
//#include <RadioMessage.h>
//#include <car/Model/Model.h>
//#include <car/Chassis/pins.h>
class Controller{
private:
//    RadioExtended* radio;
    Chassis* chassis;
//    RadioMessage* mRadioMessage;
//    CarModel* mModel;
public:
    Controller();
    void testing();
    int f(long long, long long);
    int ping(long int);
//    RadioMessage* getRadioMessage();
//    void handleMessage(RadioMessage*);

};

#endif //ROBOCAR_CONTROLLER_H
