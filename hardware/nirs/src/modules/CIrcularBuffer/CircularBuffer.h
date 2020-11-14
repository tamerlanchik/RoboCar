//
// Created by andrey on 09.11.2020.
//

#ifndef ROBOCAR_CIRCULARBUFFER_H
#define ROBOCAR_CIRCULARBUFFER_H

template<typename T>
class Iterator;

template<typename T, int capacity>
class CircularBuffer {
public:
    CircularBuffer();
    void put(T elem);
//    T&& pop();

    typedef Iterator<T> iterator;
    iterator begin();
    iterator end();

protected:
    int next(bool spy=true);
    T buffer[capacity];
    int last;
};


template<typename T>
class Iterator
{
public:
    Iterator(T * values_ptr) : values_ptr_{values_ptr}, position_{0} {}

    Iterator(T * values_ptr, int size) : values_ptr_{values_ptr}, position_{size} {}

    bool operator!=(const Iterator<T> & other) const
    {
        return !(*this == other);
    }

    bool operator==(const Iterator<T> & other) const
    {
        return position_ == other.position_;
    }

    Iterator & operator++()
    {
        ++position_;
        return *this;
    }

    T & operator*() const
    {
        return *(values_ptr_ + position_);
    }

private:
    T * values_ptr_;
    int position_;
};

#endif //ROBOCAR_CIRCULARBUFFER_H
