//
// Created by andrey on 09.11.2020.
//

#ifndef ROBOCAR_TACHOMETR_H
#define ROBOCAR_TACHOMETR_H

#include <Arduino.h>

struct TachoData {
    float x;
    float v;
    float a;
};

template<int size, int historySize>
class StaticStorage {
public:
//    void handleEvent

    volatile bool prevState[size];
    volatile unsigned long long t[size];
};

// TODO: добавить поддержку подписчиков на новые данные
class Tachometr {
public:
    Tachometr(char pin);
    virtual TachoData getData();
protected:
    void eventListener();
    void updateData();
    volatile static bool prevState[];
    volatile bool dataActual;
    TachoData prevData;
    unsigned long long t;
};


#endif //ROBOCAR_TACHOMETR_H
