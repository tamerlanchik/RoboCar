#include "Logger.h"
//#define UNIT_TEST
#ifdef UNIT_TEST
#include <Serial.h>
_Serial Serial;
#define delay(t) 0
#include <cstdarg>
#else
#include <Arduino.h>
#endif
//#include <cstdarg>




Logger::Logger(){
  Serial.begin(115200);
  delay(200);
  d("Init serial");
}

void Logger::d(const char* fmt, ...){
    Serial.print("D: ");
    va_list args;
#ifdef UNIT_TEST
    va_start(args, fmt);
    Serial.println(fmt, args);
    va_end(args);
#endif
}

void Logger::e(const char* fmt, ...){
    Serial.print("E: ");
    va_list args;
#ifdef UNIT_TEST
    va_start(args, fmt);
    Serial.println(fmt, args);
    va_end(args);
#endif
}

void Logger::i(const char* fmt, ...){
    Serial.print("I: ");
    va_list args;
#ifdef UNIT_TEST
    va_start(args, fmt);
    Serial.println(fmt, args);
    va_end(args);
#endif
}
