//
// Created by andrey on 16.05.2021.
//

#ifndef NIRS_REGULATOR_H
#define NIRS_REGULATOR_H

template<typename T>
class Regulator {
public:
    struct RegInput {};
    virtual T step(const RegInput&) = 0;
};

#endif //NIRS_REGULATOR_H
