#include "Tachometr.h"

#ifdef UNIT_TEST
    #include <modules/Logger/Logger.hpp>
#include <car/config.h>

#else
    #include <Logger.h>
#endif

StaticStorage<2, TachometrConfig::speedAccRate, TachometrConfig::accelAccRate,
    TachometrConfig::maxWinSize> Tachometr::buffer;
Tachometr* Tachometr::instances[2];

Tachometr::Tachometr(int curr) : curr(curr)  {
    Tachometr::buffer.storage[curr].mCoord.put(0);
    Log->println('d', "Init Tachometr()");
    Tachometr::instances[curr] = this;
}

// Отдает текущие координату-скорость-ускорение.
// Если старые данные не менялись, возвращаем их
// иначе считаем заново
TachoData Tachometr::getData(bool needCalc) {
    // не сможем посчитать производные
    if (Tachometr::buffer.storage[curr].mCoord.len() < TachometrConfig::speedAccRate || !needCalc || !Tachometr::buffer.storage[curr].changed) {
        return data;
    }
    auto storage = &Tachometr::buffer.storage[curr];
    data.x = storage->mCoord.at(-1);
    noInterrupts();

    calcSpeed(needCalc);
    float accel = calcAccelerate(needCalc);

    Tachometr::buffer.storage[curr].changed = false;
    interrupts();

    data.v = storage->V.buffer.at(-1) * 10e6; // ms->sec
    data.a = storage->A.buffer.at(-1) * 10e6;
    return data;
};

float Tachometr::calcSpeed(bool needCalc) {
    // не сможем посчитать производные
    if (Tachometr::buffer.storage[curr].V.buffer.len() < TachometrConfig::speedAccRate || !needCalc ||
        !Tachometr::buffer.storage[curr].changed) {
        return Tachometr::buffer.storage[curr].V.buffer.at(-1);
    }
    auto storage = &Tachometr::buffer.storage[curr];

    float dX = Tachometr::buffer.storage[curr].V.calc(
            &storage->mCoord,
            storage->dT.at(-1)
    );

    // инерционный фильтр
    const float a = tachometrConfig.aV;
    if (storage->V.buffer.len() > 1) {
        float dxFiltered = inertialFilter(a, dX, storage->V.buffer.at(-2));
        storage->V.buffer.set(-1, dxFiltered);
    }

    // оконный фильтр
    int winSize = tachometrConfig.winSizeV;
    storage->V.buffer.set(-1,
          rangeFilter(tachometrConfig.maxV, averageFilter(winSize, &storage->V.buffer))
    );
    return storage->V.buffer.at(-1);
}

float Tachometr::calcAccelerate(bool needCalc) {
    // не сможем посчитать производные
    if (Tachometr::buffer.storage[curr].V.buffer.len() < 2 ||
        Tachometr::buffer.storage[curr].A.buffer.len() < TachometrConfig::accelAccRate || !needCalc ||
        !Tachometr::buffer.storage[curr].changed) {
        return Tachometr::buffer.storage[curr].A.buffer.at(-1);
    }
    auto storage = &Tachometr::buffer.storage[curr];

    float dX = Tachometr::buffer.storage[curr].A.calc(
        &storage->V.buffer,
        (storage->V.lastTime - storage->V.prevTime) / 10e6
    );

    // инерционный фильтр
    const float a = tachometrConfig.aA;
    if (storage->A.buffer.len() > 1) {
        float dxFiltered = inertialFilter(a, dX, storage->A.buffer.at(-2));
        storage->A.buffer.set(-1, dxFiltered);
    }

    // оконный фильтр
    int winSize = tachometrConfig.winSizeA;
    // динамически подбираем размер
//    float dtAvr = 0;
//    for(int i = 0; i < Tachometr::buffer.storage[curr].mCoord.len(); ++i) {
//        dtAvr += Tachometr::buffer.storage[curr].dT.at(i);
//    }
//    dtAvr /= Tachometr::buffer.storage[curr].mCoord.len();
//
//    winSize = 1.0*WANNA_T/dtAvr + 1;
//    winSize = min(winSize, Tachometr::buffer.storage[curr].mCoord.len() - 1);

    storage->A.buffer.set(-1,
          rangeFilter(tachometrConfig.maxA, averageFilter(winSize, &storage->A.buffer))
    );
    return storage->A.buffer.at(-1);
}

TachoData Tachometr::getLinearData(bool needCalc) {
    if (needCalc) {
        getData(needCalc);
    }

    return TachoData{
        TachometrConfig::rad2lin(data.x) / TachometrConfig::LIN_MULT,
        TachometrConfig::rad2lin(data.v) / TachometrConfig::LIN_MULT,
        TachometrConfig::rad2lin(data.a) / TachometrConfig::LIN_MULT,
    };
}

template<typename T>
T Tachometr::sum(const T data[], int len) {
    T res = 0;
    for (T temp : data) {
        res += temp;
    }
    return res;
}
