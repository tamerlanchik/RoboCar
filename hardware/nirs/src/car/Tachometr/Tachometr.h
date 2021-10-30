#ifndef ROBOCAR_TACHOMETR_H
#define ROBOCAR_TACHOMETR_H

#include <Arduino.h>
#ifdef UNIT_TEST
    #include <modules/CircularBuffer/CircularBuffer.h>
    #include <modules/Logger/Logger.hpp>
    #include <modules/Math/Math.h>
template<typename T> constexpr T max(T a, T b) { return a >= b ? a : b; }
template<typename T> constexpr T min(T a, T b) { return a <= b ? a : b; }
#else
    #include <CircularBuffer.h>
    #include <Logger.h>
    #include <Math.h>
#endif
#include <Config.h>

extern Logger* Log;
extern TachometrConfig tachometrConfig;

struct TachoData {
    float x;
    float v;
    float a;
};

// для динамического вычисления окна усреднения
// желаемое "время реакции", мс
const int WANNA_T = 20 * 1000; // 20 ms

// Статическое хранилище данных тахометра
// Функции аппаратного прерывания не могут обращаться к динамическим
// переменным.
template<int count, int Kv, int Ka, int AVER>
class StaticStorage {
public:
    // Данные на один канал (датчик)
    class Data {
    public:
        CircularBuffer<float, max(Kv+2, AVER)> mCoord;            // координата
        CircularBuffer<unsigned long, max(Kv+2, AVER)> dT;
        Der<Kv, max(Ka+2, AVER)> V;             // скорость
        Der<Ka, max(1, AVER)> A;                // ускорение
        unsigned long prevT = 0;                    // время предыдущего срабатывания, для dT
        int mPath = 0;                              // суммарная координата
        int mDirection = 1;                         // коэффициент направления [-1; 1]
        bool changed;                               // значения обновились ли
        bool haltWatchdogFlag = 1;                  // если долго не сбрасываем, добавим запись 0 (стоим)

        void handleInterr(unsigned long t, float dS) volatile {
            long dt = t - prevT;
            if (dT.len() < 1) {
                dt = 10000; // 0 не годится
            }
            dT.put( dt);
            mCoord.put(mCoord.at(-1) + dS);
            changed = true;
            haltWatchdogFlag = false;
            prevT = t;
        }
        void handleInterr(unsigned long t) volatile {
            handleInterr(t, TachometrConfig::dPhi*mDirection);
        }
    };

    volatile Data storage[count];
};


// TODO: добавить поддержку подписчиков на новые данные
class Tachometr {
public:
    static StaticStorage<2,
        TachometrConfig::speedAccRate, TachometrConfig::accelAccRate,
        TachometrConfig::maxWinSize> buffer;
    int curr;
    TachoData data;

    Tachometr(int curr);

    template<int current>
    void start(char interrupt) {
        attachInterrupt(interrupt, [](){
            static bool state[2] = {1, 1};
            state[current] = !state[current];
            if (!state[current]) {
                return;
            }
            Tachometr::buffer.storage[current].handleInterr(micros());
            Tachometr::instances[current]->getData(true);
        }, CHANGE);
    }

    virtual TachoData getData(bool needCalc=true);
    virtual TachoData getLinearData(bool needCalc=true);

    template<typename T>
    static T sum(const T[], int len);

    // вызываем, если долго не было данных с датчика (остановились)
    static void handleStopFlag(int i) {
        if(Tachometr::buffer.storage[i].haltWatchdogFlag == 1) {
            noInterrupts();
            if(Tachometr::buffer.storage[i].haltWatchdogFlag == 1) {
                Tachometr::buffer.storage[i].handleInterr(micros(), 0);
            }
            interrupts();}
        Tachometr::buffer.storage[i].haltWatchdogFlag = 1;
    }

private:
    virtual float calcSpeed(bool needCalc=true);
    virtual float calcAccelerate(bool needCalc=true);
public:
    static Tachometr* instances[2]; // указатели на все объекты тахометров
};




#endif //ROBOCAR_TACHOMETR_H
