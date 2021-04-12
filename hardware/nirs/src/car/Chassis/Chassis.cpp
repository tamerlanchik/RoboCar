//#define UNIT_TEST
#include "Chassis.h"
#ifdef UNIT_TEST
#include <modules/Logger/Logger.hpp>
#include <car/config.h>
#else
//#include "modules/Logger/Logger.h"
#include <Config.h>
#endif
#include <Logger.h>

extern Logger* Log;
extern ChassisConfig chassisConfig;

const Movement Chassis::movements[] = { 0b0, 0b0101, 0b1010, 0b1001, 0b0110 };

const Movement Chassis::motorMovements[] = { 0b00, 0b01, 0b10 };

char add(char high_part, char low_part) {
    if (high_part > 0b00000011) {
        // записали в середине, сдвигаем
        high_part >>=2;
    }
    // чистим разряды
    low_part = (low_part<<6)>>6;
    high_part = (high_part<<6)>>6;
    return high_part<<2 | low_part;
}

Chassis::Chassis(){
    Log->println('d', "Create Chassis");
}

void Chassis::init(){
    for(Pin pin : motorPins){
        pinMode((byte)pin, OUTPUT);
    }
    Log->println('d', "Init Chassis");
}

// Послать сигнал на драйвера моторов
// @param a - величина "газа" линейного движения, [-255, 255]
// @param b - величина "газа" углового движения, [-255, 255]
void Chassis::setValue(int a, int b){
    // A - linear movement
    // B - angular one

    a = constrain(a, -255, 255);
    b = constrain(b, -255, 255);

    int speedA = abs(a);
    int speedB = abs(b);

    if(speedA < chassisConfig.epsMov){   // поворот на месте / стоянка
        analogWrite((byte)motorPins[4], speedB);
        analogWrite((byte)motorPins[5], speedB);
        if(abs(b) < chassisConfig.epsMov){
            writeMotors(movements[Stop]);
        }else{
            if(b > 0){
                writeMotors(movements[Right]);
            }else{
                writeMotors(movements[Left]);
            }
        }
    }else{  // едем вперед-назад
        analogWrite((byte)motorPins[4], speedA);
        analogWrite((byte)motorPins[5], speedA);
        if(a > 0){
            writeMotors(movements[Forward]);
        }else{
            writeMotors(movements[Backward]);
        }
    }
}

// Послать сигнал на драйвера моторов с вычислением дифференциала
// @param a - величина "газа" левой стороны, [-255, 255]
// @param b - величина "газа" правой стороны, [-255, 255]
void Chassis::setValue2(int a, int b){
    a = constrain(a, -255, 255);
    b = constrain(b, -255, 255);

//    auto sign = [](float v){ return v >= 0 ? 1 : -1; };
    auto chooseMotorMode = [](int speed)->Movement {
        MotorMovementIndexes idx = MotorMovementIndexes::Stop;
        if(speed >= chassisConfig.epsMov) idx = MotorMovementIndexes::Forward;
        else if (speed <= -chassisConfig.epsMov) idx = MotorMovementIndexes::Backward;
        return Chassis::motorMovements[(int)idx];
    };

    Movement movement = add(
        chooseMotorMode(a),
        chooseMotorMode(b)
    );

    writeMotors(movement);
    analogWrite((byte)motorPinsPWM[0], abs(a));
    analogWrite((byte)motorPinsPWM[1], abs(b));
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
        digitalWrite((byte)motorPins[i], byteAt(movement, i));
    }
}

bool byteAt(int src, size_t pos) {
    return src>>pos & 1;
}