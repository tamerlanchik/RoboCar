//
// Created by andrey on 03.11.2020.
//

#ifndef ROBOCAR_CHASSIS_H
#define ROBOCAR_CHASSIS_H

#include <Arduino.h>
#include "pins.h"
#ifdef UNIT_TEST
//    #include <car/config.h>
#else
//    #include <config.h>
#endif
//#include <modules/Log/Log.hpp>

//extern

typedef char Movement;
enum MoveIndexes {Stop, Forward, Backward, Right, Left};
enum class MotorMovementIndexes { Stop, Forward, Backward };

// склеиваем два байта в один по порядку
// 0b11001001: high_part = 10, low part=01
//constexpr
char add(char high_part, char low_part);

class Chassis {
public:
    enum class MotorMov {HALT=0, FORWARD, BACKWARD};
    struct MotorValues {
        int L;
        int R;
    };
    static const Movement movements[6];
    static const Movement motorMovements[3];

    Chassis();
    virtual void init();
    virtual void setValue(int,int);
    virtual void setValue2(int,int);
//    virtual void changeMoveMode(int, int);  // поворот в движении

//    void setValue(int[]);
    virtual void setMotorValues(Movement);

    virtual MotorValues getDifferential(int gaz, int rotation);

    virtual void setGazDiffValues(int,int);

    int _gaz;
    int _diff;
protected:
    virtual void writeMotors(Movement);
};

bool byteAt(int src, size_t pos);



#endif //ROBOCAR_CHASSIS_H
