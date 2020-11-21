//
// Created by andrey on 03.11.2020.
//

#ifndef ROBOCAR_PINS_H
#define ROBOCAR_PINS_H

//Nano SWM: 3.5.6.9.10.11

//pins
//REMEMBER: PIN 10 ONLY OUTPUT!
//class Pin {
//public:
//    enum { AL=0, AR, INT1, INT2, M11, M12, M21, M22, D8, PWM1, PWM2};
//
//    operator byte() const { return (byte)}
//
//};

enum class Pin { AL, AR, INTER1, INTER2, M11, M12, M21, M22, D8, PWM1, PWM2 };
const Pin motorPinsPWM[] = {Pin::PWM1, Pin::PWM2};
const Pin motorPins[] = {Pin::M11, Pin::M12, Pin::M21, Pin::M22};
const Pin tachoPins[] = {Pin::INTER1, Pin::INTER2};
const byte radioCE = 4;
const byte radioCSN = 7;

#endif //ROBOCAR_PINS_H
