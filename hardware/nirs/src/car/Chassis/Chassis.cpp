//
// Created by andrey on 03.11.2020.
//
//#define UNIT_TEST
#ifdef UNIT_TEST
#include <modules/Logger/Logger.h>
#else
#include "../Logger/Logger.h"
#endif
#include "Chassis.h"

extern Logger* Log;

Chassis::Chassis(){
    Log->d("Create Chassis");
}

void Chassis::init(){
    for(byte pin : motorPins){
        pinMode(pin, OUTPUT);
    }
    Log->d("Init Chassis");
}

void Chassis::setValue(int a, int b){
    a = constrain(a, -255, 255);
    b = constrain(b, -255, 255);

    int epsRotate = 30;
    int epsMove = 30;

    int speedA = abs(a);
    int speedB = abs(b);

    if(abs(a) < epsMove){
        analogWrite(motorPins[4], speedB);
        analogWrite(motorPins[5], speedB);
        if(abs(b) < epsRotate){
            writeMotors(Modes.Stop);
        }else{
            if(b > 0){
                writeMotors(Modes.Right);
            }else{
                writeMotors(Modes.Left);
            }
        }
    }else{
        analogWrite(motorPins[4], speedA);
        analogWrite(motorPins[5], speedA);
        if(a > 0){
            writeMotors(Modes.Forward);
        }else{
            writeMotors(Modes.Backward);
        }
    }
}

void Chassis::setValue(int value[]){
    setValue(value[0], value[1]);
}

//private
void Chassis::writeMotors(bool values[]){
    for(unsigned char i = 0; i<4; i++)
        digitalWrite(motorPins[i], values[i]);
}
