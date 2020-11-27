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
    #include <modules/Math/Math.h>
template<typename T> constexpr T max(T a, T b) { return a >= b ? a : b; }
template<typename T> constexpr T min(T a, T b) { return a <= b ? a : b; }
#else
    #include <CircularBuffer.h>
    #include <config.h>
    #include <Logger.hpp>
    #include <Math.h>
#endif

extern Logger* Log;
extern TachometrConfig tachometrConfig;


struct TachoData {
    float x;
    float v;
    float a;
};

//const int WIN_SIZE = 6;
const int WANNA_T = 20 * 1000; // 20 ms

template<int count, int K, int AVER>
class StaticStorage {
public:
    class Data {
    public:
        CircularBuffer<float, max(K+2, AVER)> mCoord;            // координата
        CircularBuffer<unsigned long, max(K+2, AVER)> dT;
        Der<K, max(K+2, AVER)> V;
        unsigned long prevT = 0;
        int mPath = 0;                              // суммарная координата
        int mDirection = 1;                         // коэффициент направления
        bool changed;                               // значения обновились
        bool haltWatchdogFlag = 1;                  // если долго не сбрасываем, добавим запись 0

        void handleInterr(unsigned long t, float dS) volatile {
            long dt = t - prevT;
            if (dT.len() < 1) {
//                dt = 0;
                dt = 10000;
            }
            dT.put( dt);
            mCoord.put(mCoord.at(-1) + dS);
            changed = true;
            haltWatchdogFlag = false;
            prevT = t;
//            Log->println('d', "handle: ", (int)(dt/1000000), (int)(dt%1000000/1000), (int)(dt%1000), mCoord.at(-1), "\n");
        }
        void handleInterr(unsigned long t) volatile {
            handleInterr(t, TachometrConfig::dL*mDirection);
        }
    };

    volatile Data storage[count];
};


const int ACC_RATE = 1;
// TODO: добавить поддержку подписчиков на новые данные
class Tachometr {
public:
    static StaticStorage<2, ACC_RATE, TachometrConfig::maxWinSize> buffer;
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
            Tachometr::buffer.storage[current].handleInterr(micros());
            Tachometr::instances[current]->getData(true);
//            Log->println('d', "handlle");

        }, CHANGE);
    }
    virtual TachoData getData(bool needCalc=true);
    template<typename T>
    static T sum(const T[], int len);
    static void handleStopFlag(int i) {
        if(Tachometr::buffer.storage[i].haltWatchdogFlag == 1) {
            noInterrupts();
            if(Tachometr::buffer.storage[i].haltWatchdogFlag == 1) {
                Tachometr::buffer.storage[i].handleInterr(micros(), 0);
            }
            interrupts();}
        Tachometr::buffer.storage[i].haltWatchdogFlag = 1;
    }
public:
    void updateData();
    static Tachometr* instances[2];
};




#endif //ROBOCAR_TACHOMETR_H
