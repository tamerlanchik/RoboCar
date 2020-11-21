#include "Tachometr.h"

#ifdef UNIT_TEST
    #include <modules/Logger/Logger.hpp>
#else
    #include <Logger.hpp>
#endif

StaticStorage<long long, 2, ACC_RATE> Tachometr::buffer;

Tachometr::Tachometr(int curr) : curr(curr)  {
    Log->println('d', "Init Tachometr()");
}

// Отдает текущие координату-скорость-ускорение.
// Если старые данные не менялись, возвращаем их
// иначе считаем заново
TachoData Tachometr::getData() {
    long long int start = micros();
//    if (!Tachometr::buffer.changed[curr]) {
//        return data;
//    }
    int v_new = 0;
    data.x = Tachometr::buffer.mPath[curr];
    int currX = data.x;

//    noInterrupts();
    // восстанавливаем вектор координаты по текущему значению и истории приращений.
    long long prevTime, currTime = Tachometr::buffer.mTime[curr].at(-1);
    Log->println('d', "Start calc: currX=", currX, (int)(currTime/1000), (int)(currTime % 1000));
    for(int i = Tachometr::buffer.mTime[curr].len() - 1; i > 0; --i) {
        prevTime = Tachometr::buffer.mTime[curr].at(i - 1);
        Log->println('d', v_new, WEIGHTS[i-1]);
//        Log->println('d', (int)((currTime - prevTime)/1000), (int)((currTime - prevTime) % 1000));
//        Log->println('d', currX, currX * WEIGHTS[i-1]);
        v_new += (currX * WEIGHTS[i-1] / (currTime - prevTime));
        currTime = prevTime;
        currX -= Tachometr::buffer.mCoord[curr].at(i);
        Log->println('d', "iter: ", v_new, (int)(currTime/1000), (int)(currTime % 1000), currX);
    }
//    interrupts();
    data.v = 1.0*v_new * 1000000; // ms->sec
    data.v /= MULIPLIER; // веса
    data.v /= LIN_MULT; // dL
    data.x /= LIN_MULT;
    Tachometr::buffer.changed[curr] = false;
//    Log->println('d', "getData() ", (int)(micros() - start));
    return data;
};

template<typename T>
T Tachometr::sum(const T data[], int len) {
    T res = 0;
    for (T temp : data) {
        res += temp;
    }
    return res;
}
//void Tachometr::eventListener() {
//
//}

void Tachometr::updateData() {

};