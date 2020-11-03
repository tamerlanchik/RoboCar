//
// Created by andrey on 03.11.2020.
//

#ifndef ROBOCAR_CONTROLLER_H
#define ROBOCAR_CONTROLLER_H

#ifdef UNIT_TEST
#include "modules/Logger/Logger.hpp"
#include "car/Chassis/Chassis.h"
#include <car/config.h>
#include <car/Model/Model.h>
#include <modules/Communicator/Communicator.h>
#else
#include <Logger.hpp>
#include <Chassis.h>
#include <config.h>
#include <Model.h>
#include <Communicator.h>
#endif
#include <Arduino.h>

//#include <RadioExtended.h>
//#include <RadioMessage.h>
//#include <car/Model/Model.h>
//#include <car/Chassis/pins.h>
class Controller{
private:
//    RadioExtended* radio;
    Communicator* comm;
    Chassis* chassis;
//    RadioMessage* mRadioMessage;
    Model* mModel;
public:
    Controller();
    void testing();
    int f(long long, long long);
    int ping(long int);
    Communicator* getCommunicator();
//    RadioMessage* getRadioMessage();
//    void handleMessage(RadioMessage*);


};

enum class Commands {PING='A'};

#endif //ROBOCAR_CONTROLLER_H
