//
// Created by andrey on 09.11.2020.
//

#ifndef ROBOCAR_TACHOMETR_H
#define ROBOCAR_TACHOMETR_H

#include <Arduino.h>
#ifdef UNIT_TEST
    #include <modules/CircularBuffer/CircularBuffer.h>
    #include <car/config.h>
    #include <modules/Logger/Logger.hpp>
#else
    #include <CircularBuffer.h>
    #include <config.h>
    #include <Logger.hpp>
#endif

struct TachoData {
    float x;
    float v;
    float a;
};

const int MULIPLIER = 100;
// 4й порядок точности
//const int WEIGHTS[] = {
//        (int)(0.25*100),
//        (int)(-1.333*100),
//        (int)(3*100),
//        (int)(-4*100),
//        (int)(2.0822*100),
//        };

const int WEIGHTS[] = {
        (int)(-1*MULIPLIER),
        (int)(1*MULIPLIER),
};

template<typename T, int count, int K>
class StaticStorage {
public:
    volatile CircularBuffer<unsigned long, K+2> mTime[count];   // время тика
    volatile CircularBuffer<int, K+2> mCoord[count];  // прирост координаты

    volatile int mPath[count] = {0,0};              // пройденное расстояние
    int mDirection[count] = {1, 1};                 // коэффициент направления

    volatile bool changed[count];
    volatile bool haltWatchdogFlag[count] = {1, 1}; // если долго не сбрасываем, добавим запись 0
};

extern Logger* Log;

const int ACC_RATE = 1;
// TODO: добавить поддержку подписчиков на новые данные
class Tachometr {
public:
    static StaticStorage<long long, 2, ACC_RATE> buffer;
    int curr;
    TachoData data;

    Tachometr(int curr);
    template<int current>
    void start(char interrupt) {
        Log->println('d', "Start()");
        attachInterrupt(interrupt, [](){
            static bool state[2] = {1, 1};
            state[current] = !state[current];
            if (!state[current]) {
                return;
            }
            unsigned long t = micros();
            Tachometr::buffer.mTime[current].put(t);
            Tachometr::buffer.mCoord[current].put(Tachometr::buffer.mDirection[current] * dL);
            Tachometr::buffer.changed[current] = true;
            Tachometr::buffer.mPath[current] += Tachometr::buffer.mDirection[current] * dL;
            Tachometr::buffer.haltWatchdogFlag[current] = false;    // сбросили флаг
//             Tachometr::print("Interrupt()");
            Log->println('d', "inter: ", (int)(t/1000000), (int)(t % 1000000/1000), (int)(t % 1000));

        }, CHANGE);
    }
    virtual TachoData getData();
    template<typename T>
    static T sum(const T[], int len);
    static void print() {
        // Log->println('d', "Star()");
    }
    static void handleStopFlag(int i) {
        if(Tachometr::buffer.haltWatchdogFlag[i] == 1) {
            noInterrupts();
            if(Tachometr::buffer.haltWatchdogFlag[i] == 1) {
                Tachometr::buffer.mTime[i].put(micros());
                Tachometr::buffer.mCoord[i].put(0);
                Tachometr::buffer.changed[i] = true;
            }
            interrupts();
            auto t = micros();
            Log->println('d', "inter2: ", (int)(t/1000000), (int)(t % 1000000/1000), (int)(t % 1000));
        }
        Tachometr::buffer.haltWatchdogFlag[i] = 1;
    }
public:
    void updateData();
};




#endif //ROBOCAR_TACHOMETR_H
