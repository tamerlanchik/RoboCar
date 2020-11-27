#include "Tachometr.h"

#ifdef UNIT_TEST
    #include <modules/Logger/Logger.hpp>
#include <car/config.h>

#else
    #include <Logger.hpp>
#endif

StaticStorage<2, ACC_RATE, TachometrConfig::maxWinSize> Tachometr::buffer;
Tachometr* Tachometr::instances[2];

Tachometr::Tachometr(int curr) : curr(curr)  {
    Tachometr::buffer.storage[curr].mCoord.put(0);
    Log->println('d', "Init Tachometr()");
    Tachometr::instances[curr] = this;
}

void ff(Array<float>* a);

// Отдает текущие координату-скорость-ускорение.
// Если старые данные не менялись, возвращаем их
// иначе считаем заново
TachoData Tachometr::getData(bool needCalc) {
    // не сможем посчитать производные
    if (Tachometr::buffer.storage[curr].mCoord.len() < ACC_RATE + 1 || !needCalc || !Tachometr::buffer.storage[curr].changed) {
        return data;
    }
    auto storage = &Tachometr::buffer.storage[curr];
//    Log->println('d', "getData");

    data.x = storage->mCoord.at(-1);
    noInterrupts();

     float dX = Tachometr::buffer.storage[curr].V.calc(
             &storage->mCoord,
             storage->dT.at(-1)
     );

    // инерционный фильтр
    const float a = tachometrConfig.a;
    if (storage->V.buffer.len() > 1) {
        float dxFiltered = inertialFilter(a, dX, storage->V.buffer.at(-2));
        storage->V.buffer.set(-1, dxFiltered);
    }

    // оконный фильтр
    int winSize = tachometrConfig.winSize;
    // динамически подбираем размер
//    float dtAvr = 0;
//    for(int i = 0; i < Tachometr::buffer.storage[curr].mCoord.len(); ++i) {
//        dtAvr += Tachometr::buffer.storage[curr].dT.at(i);
//    }
//    dtAvr /= Tachometr::buffer.storage[curr].mCoord.len();
//
//    winSize = 1.0*WANNA_T/dtAvr + 1;
//    winSize = min(winSize, Tachometr::buffer.storage[curr].mCoord.len() - 1);

    storage->V.buffer.set(-1,
            averageFilter(winSize, &storage->V.buffer)
    );

    Tachometr::buffer.storage[curr].changed = false;
    interrupts();

    data.v = storage->V.buffer.at(-1) * 10e6; // ms->sec
//    data.v /= MULIPLIER; // веса
    data.v /= TachometrConfig::LIN_MULT; // dL
    data.x /= TachometrConfig::LIN_MULT;
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