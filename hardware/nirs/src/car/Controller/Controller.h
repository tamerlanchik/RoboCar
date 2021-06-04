#ifndef ROBOCAR_CONTROLLER_H
#define ROBOCAR_CONTROLLER_H

#ifdef UNIT_TEST
    #include "modules/Logger/Logger.hpp"
    #include "car/Chassis/Chassis.h"
    #include <car/Model/Model.h>
    #include <modules/Communicator/Communicator.h>
    #include <car/Tachometr/Tachometr.h>
    #include <leOS2Mock/leOS2Mock.h>
    typedef leOS2Mock leOS2;
#else
    #include <Logger.h>
    #include <Chassis.h>
    #include <Model.h>
    #include <Communicator.h>
//    #include <Tachometr.h>
    #include <leOS2.h>
    #include <Config.h>
    #include <Vector.h> // грязный хак - platformio не находит в Communicator.h
#endif
#include <Arduino.h>
//#include "car/Chassis/Chassis.h"
//#include <car/Model/Model.h>
//#include <modules/Communicator/Communicator.h>
//#include <car/Tachometr/Tachometr.h>


class Controller{
//protected:
public:
    Communicator* comm;
    Chassis* chassis;
    Model* mModel;
//    Tachometr* tachometer[2];
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
//    virtual Tachometr* getTachometr();
};

enum class Commands {PING='A'};

#endif //ROBOCAR_CONTROLLER_H
