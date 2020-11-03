//
// Created by andrey on 03.11.2020.
//

#ifndef ROBOCAR_CHASSIS_H
#define ROBOCAR_CHASSIS_H


#if !defined HEADERCHASSIS
#define HEADERCHASSIS
#include <Arduino.h>
#include "pins.h"
//#include <modules/Log/Log.hpp>
struct MOVING_MODES{
    bool Stop[4];
    bool Forward[4];
    bool Backward[4];
    bool Right[4];
    bool Left[4];
};

class Chassis
{
private:
    MOVING_MODES Modes = {
            {0,0,0,0},
            {0,1,0,1},
            {1,0,1,0},
            {1,0,0,1},
            {0,1,1,0}
    };
    void writeMotors(bool[]);
public:
    Chassis();
    void init();
    void setValue(int,int);
    void setValue(int[]);
};

#endif



#endif //ROBOCAR_CHASSIS_H
