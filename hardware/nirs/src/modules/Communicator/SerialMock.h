//
// Created by andrey on 03.11.2020.
//

#ifndef ROBOCAR_SERIALMOCK_H
#define ROBOCAR_SERIALMOCK_H
#include <modules/Logger/Logger.h>

extern Logger* Log;
class SerialMock{
public:
    SerialMock() : value(nullptr), i(0), buf_size(0) {}
    void begin(int rate) {}

    template<typename T>
    void print(T value) {
        Log->setDivider("");
        Log->print_rec(value);
        Log->rollbackDivider();
    }

    template<typename T>
    void println(T value) {

        Log->setDivider("");
        Log->print_rec(value);
        Log->print_rec("\n");
        Log->rollbackDivider();
    }

    int available() {
        return i < buf_size;
    }

    int read() {
        if (i >= buf_size) {
            return -1;
        }
        return value[i++];
    }

    void WillReturnRead(const char* val, size_t size) {
        value = val;
        buf_size = size;
        i = 0;
    }
private:
    const char* value;
    size_t buf_size;
    size_t i;
};

#endif //ROBOCAR_SERIALMOCK_H
