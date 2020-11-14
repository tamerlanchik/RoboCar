//
// Created by andrey on 09.11.2020.
//

#include "CircularBuffer.h"

template<typename T, int capacity>
CircularBuffer<T, capacity>::CircularBuffer() : last(0) {}

template<typename T, int capacity>
void CircularBuffer<T, capacity>::put(T elem) {
    buffer[next(false)] = elem;
}

template<typename T, int capacity>
int CircularBuffer<T, capacity>::next(bool spy) {
    int nextIdx = last++;
    if (nextIdx >= sizeof(buffer)) {
        nextIdx = 0;
    }
    if (!spy) {
        last = nextIdx;
    }
    return nextIdx;
}
template<typename T, int capacity>
typename CircularBuffer<T, capacity>::iterator CircularBuffer<T, capacity>::begin() {
    return iterator(buffer, next());
}

template<typename T, int capacity>
typename CircularBuffer<T, capacity>::iterator CircularBuffer<T, capacity>::end() {
    return iterator(buffer, last);
}
