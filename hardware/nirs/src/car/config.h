//
// Created by andrey on 03.11.2020.
//

#ifndef ROBOCAR_CONFIG_H
#define ROBOCAR_CONFIG_H

const float EPS_MOV = 10;   // мертвый ход движения
const int LIN_MULT = 1000;
const int dL = LIN_MULT * (0.205/23);

const unsigned int SERIAL_BAUDRATE = 57600;

const byte INTERRUPT0 = 0;

#endif //ROBOCAR_CONFIG_H
