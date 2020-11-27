//
// Created by andrey on 27.11.2020.
//

#ifndef ROBOCAR_DER_H
#define ROBOCAR_DER_H

const int WEIGHTS_1[] = { -1, 1};

template<int acc_rate, int buffer_len>
class Der {
public:
    Der() {
        for (int i = 0; i < acc_rate; ++i) {
            buffer.put(0);
        }
    }
    float calc(volatile Array<float>* f, float dt) volatile {
        float df = 0;
        int points = f->len();
        // j - по весам
        // i - по точкам
        for(int i = points - acc_rate-1, j=0; i < points; ++i, ++j) {
            df = df + WEIGHTS_1[j]*f->at(i);
        }
        df /= dt;
        buffer.put(df);
        return df;
    }
    CircularBuffer<float, buffer_len> buffer;
};

#endif //ROBOCAR_DER_H
