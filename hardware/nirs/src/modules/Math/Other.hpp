//
// Created by andrey on 27.11.2020.
//

#ifndef ROBOCAR_INERTIALFILTER_H
#define ROBOCAR_INERTIALFILTER_H

template<typename T>
T inertialFilter(const float a, const T curr, const T prev) {
    return a*curr + (1 - a)*prev;
}

template<typename T>
T averageFilter(const int winSize, volatile Array<T>* data) {
    float avr = 0;
    for(int i = data->len() - 1, j = 0; j < winSize && i > 0; --i, ++j) {
        avr += data->at(i);
    }
    return avr / winSize;
}

template<typename T>
T rangeFilter(const T maxVal, volatile T val) {
    val = val > maxVal ? maxVal : val;
    val = val < -maxVal ? -maxVal : val;
    return val;
}

#endif //ROBOCAR_INERTIALFILTER_H
