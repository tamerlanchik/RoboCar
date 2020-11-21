#ifndef ROBOCAR_CIRCULARBUFFER_H
#define ROBOCAR_CIRCULARBUFFER_H

template<typename T, int capacity>
class CircularBuffer {
public:
    CircularBuffer() : count(0), last(-1){}
    void put(T elem) volatile {
        buffer[next()] = elem;
        if (count < capacity) {
            ++count;
        }
    }

    int next() volatile {
        last = f(last + 1);
        return last;
    }

    int len() volatile { return count; }
    int cap() volatile { return capacity; }

    T at(int i) volatile{
        return buffer[f(last - (count - 1) + i)];
    }
protected:
    int f(int val) volatile{
        if (val < 0) {
            val =  capacity + val;
        }

        if(val >= capacity) {
            val = capacity - val;
        }
        return val;
    }
    T buffer[capacity];
    int last;
    int count;
};

#endif //ROBOCAR_CIRCULARBUFFER_H
