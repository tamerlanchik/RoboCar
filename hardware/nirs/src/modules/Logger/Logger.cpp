#include "Logger.h"

Logger::Logger() : divider(" "), prev_divider(divider) {
#ifdef UNIT_TEST
    //        println('i', "Init serial");
#else
    Serial.begin(communicatorConfig.baudrate);
    delay(200);
#endif
    println('i', "Init serial");
}

//template<typename ...Params>
//void Logger::println(const char level, Params... params) {
//    const char *prefix;
//    switch (level) {
//        case 'd': prefix = "D: "; break;
//        case 'i': prefix = "I: "; break;
//        case 'e': prefix = "E: "; break;
//        default: prefix = "";
//    }
//    print_rec(prefix);
//    print_rec(params...);
//    print_rec("\n");
//}

//template<typename T, typename... Params>
//void Logger::print_rec(T value, Params... params) {
//#ifdef UNIT_TEST
//    std::cout << value << divider;
//#else
//    Serial.print(value);
//    Serial.print(divider);
//#       endif
//    print_rec(params...);
//}

//template<typename T>
//void Logger::print_rec(T value) {
//#ifdef UNIT_TEST
//    std::cout << value;
//#else
//    Serial.print(value);
//#endif
//}

void Logger::setDivider(const char* d) {
    prev_divider = divider;
    divider = d;
}

void Logger::rollbackDivider() {
    divider = prev_divider;
}