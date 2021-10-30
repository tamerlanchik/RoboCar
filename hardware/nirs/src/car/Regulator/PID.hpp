//
// Created by andrey on 16.05.2021.
//

#ifndef NIRS_PID_HPP
#define NIRS_PID_HPP

#include "Regulator.h"
#include "Arduino.h"

struct Coefficients {
    float P;    // proportional
    float I;    // integral
    float D;    // derivative
};

template<typename T>
class PID : public Regulator<T>{
public:
    struct PIDInput : public Regulator<T>::RegInput {
        T signal;
        T der;
        T integral;
    };
    PID(T p, T i, T d) : _c{p, i, d} {
        _h = micros();
    }

    virtual T step(const PIDInput& value) {

    }
private:
    Coefficients _c;
    float _integral;
    float _derivative;
    unsigned int _h;    // time space since last call
};


#endif //NIRS_PID_HPP
