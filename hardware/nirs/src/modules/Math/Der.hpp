/*
 * Класс - дифференциатор.
 * Считает производную методом конечных разностей
 * заданного порядка.
 */

#ifndef ROBOCAR_DER_H
#define ROBOCAR_DER_H

// коэффициенты для конечных разностей
const float WEIGHTS_1[] = { -1, 1};
const float WEIGHTS_2[] = {0.5, -2, 1.5};
const float WEIGHTS_4[] = {0.25, -1.3333, 3, -4, 2.0833};

template<int acc_rate, int buffer_len>
class Der {
public:
    Der() : lastTime(0), prevTime(0) {
        for (int i = 0; i < acc_rate; ++i) {
            buffer.put(0);
        }
    }
    float calc(volatile Array<float>* f, float dt) volatile {
        const float* WEIGHTS[] = {nullptr, WEIGHTS_1, WEIGHTS_2, nullptr, WEIGHTS_4};
        float df = 0;
        int points = f->len();
        // j - по весам
        // i - по точкам
        for(int i = points - acc_rate-1, j=0; i < points; ++i, ++j) {
            df = df + WEIGHTS[acc_rate][j]*f->at(i);
        }
        df /= dt;
        buffer.put(df);
        prevTime = lastTime;
        lastTime = micros();
        return df;
    }
    CircularBuffer<float, buffer_len> buffer;
    // для последующих вычислителей
    // время получения данных
    unsigned long lastTime;
    unsigned long prevTime;
};

#endif //ROBOCAR_DER_H
