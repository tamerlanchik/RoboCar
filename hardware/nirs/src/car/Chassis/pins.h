//
// Created by andrey on 03.11.2020.
//

#ifndef ROBOCAR_PINS_H
#define ROBOCAR_PINS_H

//Nano SWM: 3.5.6.9.10.11

//pins
//REMEMBER: PIN 10 ONLY OUTPUT!
const byte motorPins[] = {4,5,6,7};
const byte motorPinsPWM[] = {9, 10};
enum class Pins { AL=0, AR, D1=0, D2, D3, D4, INT1=2, INT2=3};
const Pins tachoPins[] = {Pins::INT1, Pins::INT2};
const byte radioCE = 4;
const byte radioCSN = 7;

#endif //ROBOCAR_PINS_H
