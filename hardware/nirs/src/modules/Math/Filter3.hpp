#ifndef NIRS_FILTER3_H
#define NIRS_FILTER3_H

#include "Math3D.h"

template<class T>
class Filter3 {
public:
    virtual T apply(const T& value) = 0;

    virtual T get() = 0;
};

template<class T>
class DummyFilter : public Filter3<T> {
public:
    T apply(const T& value) {
        _prev = value;
        return get();
    }
    T get() {
        return _prev;
    }
private:
    T _prev;
};

template<class T>
class AverageFilter : public Filter3<T> {
public:
    AverageFilter(const float factor, T init_val) : _factor(factor), _prev(init_val) {}

    T apply(const T& new_val) {
        _prev = new_val*_factor + _prev*(1-_factor);
        return get();
    }

    T get() {
        return _prev;
    }
private:
    float _factor;
    T _prev;
};

#endif //NIRS_FILTER3_H
