//
// Created by andrey on 19.10.2020.
//

#include "Utils.h"
#define TEST
#ifdef TEST
#include <arduino-mock/include/arduino-mock/Arduino.h>
#else
#include <Arduino.h>
#endif

void Utils::sleep(long millis) {
    delay(millis);
}