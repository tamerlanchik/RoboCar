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
    #include <car/Tachometr/Tachometr.h>
    #include <leOS2Mock/leOS2Mock.h>
    typedef leOS2Mock leOS2;
#else
#include <Logger.hpp>
#include <Chassis.h>
#include <config.h>
#include <Model.h>
#include <Communicator.h>
#include <Tachometr.h>
#include <leOS2.h>
#endif
#include <Arduino.h>



//#include <RadioExtended.h>
//#include <RadioMessage.h>
//#include <car/Model/Model.h>
//#include <car/Chassis/pins.h>
class Controller{
//protected:
public:
    Communicator* comm;
    Chassis* chassis;
    Model* mModel;
    Tachometr* tachometer[2];
    leOS2 os;
public:
    Controller();
    virtual void run() {}
    virtual void setup() {}
    virtual void testing();
    virtual int f(long long, long long);
    virtual int ping(long int);
    virtual Communicator* getCommunicator();
    virtual Chassis* getChassis();
    virtual Tachometr* getTachometr();
};

enum class Commands {PING='A'};

#endif //ROBOCAR_CONTROLLER_H
