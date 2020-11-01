//
// Created by andrey on 19.10.2020.
//
#define TEST
#include "Pin.h"
#ifdef TEST
//#include <ArduinoFake/src/Arduino.h>
#include <arduino-mock/include/arduino-mock/Arduino.h>
#else
#include <Arduino.h>
#endif

Pin::Pin(Code pin, Mode mode) : _pin(pin), _mode(mode), _connected(false) {
    this->reconnect(_pin, _mode);
}

void Pin::reconnect(Code pin, Mode mode) {
    ::pinMode((uint8_t)pin, (uint8_t)mode);
    _pin = pin;
    _mode = mode;
}

bool Pin::digitalRead() {
    return ::digitalRead(_pin);
}

float Pin::analogRead() {
    return ::analogRead(_pin);
}

void Pin::digitalWrite(bool val) {
    ::digitalWrite(_pin, (uint8_t)val);
}

void Pin::analogWrite(float val) {
    ::analogWrite(_pin, val);
}

Pin::Code Pin::getCode() { return _pin; }

Pin::Mode Pin::getMode() { return _mode; }