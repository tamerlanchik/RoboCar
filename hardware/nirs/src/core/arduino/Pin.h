//
// Created by andrey on 19.10.2020.
//

#ifndef ROBOCAR_PIN_H
#define ROBOCAR_PIN_H

#include <core/controller_interface/IPin.h>


class Pin : public IPin {
public:
    Pin(Code pin, Mode mode);
    void digitalWrite(bool);
    bool digitalRead();
    void analogWrite(float);
    float analogRead();
    void reconnect(Code pin, Mode);
    Mode getMode();
    Code getCode();
    ~Pin();
private:
    int _pin;
    Mode _mode;
    bool _connected;
};


#endif //ROBOCAR_PIN_H
