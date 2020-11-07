//#define UNIT_TEST
#ifdef UNIT_TEST
#include <modules/Logger/Logger.hpp>
#else
#include "../Logger/Logger.hpp"
#endif
#include "Chassis.h"

extern Logger* Log;

Chassis::Chassis(){
    Log->println('d', "Create Chassis");
}

void Chassis::init(){
    for(byte pin : motorPins){
        pinMode(pin, OUTPUT);
    }
    Log->println('d', "Init Chassis");
}

// Послать сигнал на драйвера моторов
// @param a, b - величина "газа", [-255, 255]
void Chassis::setValue(int a, int b){
    a = constrain(a, -255, 255);
    b = constrain(b, -255, 255);

    // величина мертвого хода от нуля
    // (для железных джойстиков)
    int epsRotate = 30;
    int epsMove = 30;

    // A - linear movement
    // B - angular one
    int speedA = abs(a);
    int speedB = abs(b);

    if(abs(a) < epsMove){   // поворот на месте / стоянка
        analogWrite(motorPins[4], speedB);
        analogWrite(motorPins[5], speedB);
        if(abs(b) < epsRotate){
            writeMotors(movements[Stop]);
        }else{
            if(b > 0){
                writeMotors(movements[Right]);
            }else{
                writeMotors(movements[Left]);
            }
        }
    }else{  // едем вперед-назад
        analogWrite(motorPins[4], speedA);
        analogWrite(motorPins[5], speedA);
        if(a > 0){
            writeMotors(movements[Forward]);
        }else{
            writeMotors(movements[Backward]);
        }
    }
}

//void Chassis::setValue(int value[]){
//    setValue(value[0], value[1]);
//}

void Chassis::setMotorValues(Movement movement){
    writeMotors(movement);
}


//private
void Chassis::writeMotors(Movement movement){
    for(size_t i = 0; i < 4; i++) {
//    for(unsigned char i = 0; i<4; i++)
        digitalWrite(motorPins[i], byteAt(movement, i));
    }
}

bool byteAt(int src, size_t pos) {
    return src>>pos & 1;
}