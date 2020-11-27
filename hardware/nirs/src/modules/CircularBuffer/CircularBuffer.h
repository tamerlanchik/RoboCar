#ifndef ROBOCAR_CIRCULARBUFFER_H
#define ROBOCAR_CIRCULARBUFFER_H

template<typename T>
class Array {
public:
    virtual T at(int i) volatile = 0;
    virtual int len() volatile = 0;
    virtual void set(int, T) volatile = 0;
};

template<typename T, int capacity>
class CircularBuffer : public Array<T> {
public:
    CircularBuffer() : count(0), last(-1){
        for(int i = 0; i < capacity; ++i)
            buffer[i] = 0;
    }
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
        return buffer[f(last - (count - 1) + i, count)];
    }

    void set(int i, T val) volatile {
        buffer[f(last - (count - 1) + i, count)] = val;
    }

protected:
    int f(int val, int lim=capacity) volatile{
        if (val < 0) {
            val =  lim + val;
        }

        if(val >= lim) {
            val = lim - val;
        }
        return val;
    }
    T buffer[capacity];
    int count;
    int last;
};

#endif //ROBOCAR_CIRCULARBUFFER_H
