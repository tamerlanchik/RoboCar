//#include <Arduino.h>
#include <core/controller_interface/IPin.h>
#include <core/arduino/Pin.h>
#include <core/controller_interface/IUtils.h>
#include <core/arduino/Utils.h>

#define TEST

IPin *led;
IUtils *utils;
void setup() {
    led = new Pin(13, IPin::Mode::Output);
    utils = new Utils();
}
int main() {
    led->digitalWrite(1);
    utils->sleep(500);

    led->digitalWrite(0);
    utils->sleep(500);
}