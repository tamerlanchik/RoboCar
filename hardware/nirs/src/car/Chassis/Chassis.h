//
// Created by andrey on 03.11.2020.
//

#ifndef ROBOCAR_CHASSIS_H
#define ROBOCAR_CHASSIS_H

#include <Arduino.h>
#include "pins.h"
//#include <modules/Log/Log.hpp>
typedef char Movement;
enum MoveIndexes {Stop, Forward, Backward, Right, Left};

class Chassis {
public:
    constexpr static const Movement movements[] = {0b0, 0b0101, 0b1010, 0b1001, 0b0110};

    Chassis();
    virtual void init();
    virtual void setValue(int,int);

//    void setValue(int[]);
    virtual void setMotorValues(Movement);

protected:
    virtual void writeMotors(Movement);
};

bool byteAt(int src, size_t pos);



#endif //ROBOCAR_CHASSIS_H
