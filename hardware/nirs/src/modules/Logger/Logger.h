#ifndef ROBOCAR_LOGGER_H
#define ROBOCAR_LOGGER_H

/* Класс для логгирования. Поддерживает моки для Serial.
 * Функции печати основаны на рекурсивных шаблонах.
 * Имеет смысл ограничить спектр входных параметров по проекту
 * во избежание превышения флеш-памяти программы.
 */

#ifdef UNIT_TEST
    #include <iostream>
#else
    #include <Arduino.h>
#endif
//#include <car/Config/Config.h>
#include <Config.h>

extern CommunicatorConfig communicatorConfig;

class Logger {
public:
    Logger();
    template<typename ...Params>
    void println(const char level, Params... params) {
        const char *prefix;
        switch (level) {
            case 'd': prefix = "D: "; break;
            case 'i': prefix = "I: "; break;
            case 'e': prefix = "E: "; break;
            default: prefix = "";
        }
        print_rec(prefix);
        print_rec(params...);
        print_rec("\n");
    }

//  Рекурсивная функция печати на шаблонах.
    template<typename T, typename... Params>
    void print_rec(T value, Params... params) {
#ifdef UNIT_TEST
        std::cout << value << divider;
#else
        Serial.print(value);
        Serial.print(divider);
#       endif
        print_rec(params...);
    }

//  для окончания рекурсии
    template<typename T>
    void print_rec(T value) {
#ifdef UNIT_TEST
        std::cout << value;
#else
        Serial.print(value);
#endif
    }

//    void print_rec() {}

//  Для удобства записи логгирующих данных ставим разделителем пробел
//  Для вывода парсируемой информации разделитель убираем
    void setDivider(const char* d);

    void rollbackDivider();

private:
    const char* divider;        // текущий разделитель
    const char* prev_divider;   // сохраненный для отката
};

#endif