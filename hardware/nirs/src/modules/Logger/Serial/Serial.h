//
// Created by andrey on 03.11.2020.
//

#ifndef ROBOCAR_SERIAL_H
#define ROBOCAR_SERIAL_H
#ifdef UNIT_TEST
#include <iostream>
#include <cstdarg>
#endif

class _Serial {
public:
    void begin(int);
//    template<typename T>

    void println(const char* fmt, ...) {
#ifdef UNIT_TEST
        va_list args;
        va_start(args, fmt);
        println(fmt, args);
        va_end(args);
#endif
    }
#ifdef UNIT_TEST
    void println(const char* fmt, va_list args) {
        print(fmt, args);
        printf("\n");
    }
#endif

    void print(const char* fmt, ...) {
#ifdef UNIT_TEST
        va_list args;
        va_start(args, fmt);
        print(fmt, args);
        va_end(args);
#endif
    }
#ifdef UNIT_TEST
    void print(const char* fmt, va_list args) {
        vprintf(fmt, args);
    }
#endif
};

void delay(int);

//extern _Serial serial;

//extern Serial;


#endif //ROBOCAR_SERIAL_H
