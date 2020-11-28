#ifndef ROBOCAR_CONFIG_H
#define ROBOCAR_CONFIG_H

#include <Arduino.h>

const float EPS_MOV = 10;   // мертвый ход движения
//const int LIN_MULT = 1000;
//const float dL = LIN_MULT * (0.205/23);

//const unsigned int SERIAL_BAUDRATE = 57600;

const byte INTERRUPT0 = 0;
const byte INTERRUPT1 = 1;

struct TachometrConfig {
    int winSizeV;
    float aV;
    float maxV;

    int winSizeA;
    float aA;
    float maxA;

    static const int LIN_MULT = 1000;
    static constexpr float dL = LIN_MULT * (0.205/23);
    static constexpr float dPhi = 2*3.1415 / 23;
    static const int maxWinSize = 10;
    // степень точности интегрирования
    static const int speedAccRate = 1;
    static const int accelAccRate = 1;

    static constexpr float rad2lin(const float rad) {
        return rad * (dL / dPhi);
    }
};

struct CommunicatorConfig {
    int cmdCount;
    char cmdInit;
    bool isTextMode;
    long int baudrate;
};

struct ChassisConfig {
    float epsMov;
};

class Config {
public:
    CommunicatorConfig* comm;
    TachometrConfig* tacho;
    ChassisConfig* chassis;
    void update(const String* name, const char* value);
};

#endif //ROBOCAR_CONFIG_H
