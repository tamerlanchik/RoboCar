/*
 * Классы с конфигурационными данными.
 * Часть данных поддерживает динамическое переназначение.
 * TODO: научить записывать в EEPROM
 */
#ifndef ROBOCAR_CONFIG_H
#define ROBOCAR_CONFIG_H

#include <Arduino.h>

const byte INTERRUPT0 = 0;
const byte INTERRUPT1 = 1;

struct TachometrConfig {
    // скорость
    int winSizeV;
    float aV;
    float maxV;

    // ускорение
    int winSizeA;
    float aA;
    float maxA;

    static const int LIN_MULT = 1000;   // мультипликатор линейных размеров (изначально для точных вычислений)
    static constexpr float dL = LIN_MULT * (0.205/23);  // расстояние за оборот, 1000*м)
    static constexpr float dPhi = 2*3.1415 / 23;    // угол за оборот, рад)
    static const int maxWinSize = 10;   // максимально возможный размер окна (для выделения места)
    // степень точности интегрирования
    static const int speedAccRate = 1;
    static const int accelAccRate = 1;

    static constexpr float rad2lin(const float rad) {
        return rad * (dL / dPhi);
    }
};

struct CommunicatorConfig {
    // команды обозначаем заглавной буквой
    // должны идти по порядку
    int cmdCount;   // число команд
    char cmdInit;   // с какой начинаем
    bool isTextMode;
    long int baudrate;
};

struct ChassisConfig {
    float epsMov;   // мертвый ход джойстика для диапазона [0; 255]
};

struct ControlConfig {
    float Kp;
    float Ki;
    float Kd;
    float errIntegrAddFactor;
    long int timeIntegrDivider;
    float wFactor;

    bool update(const String* name, const char* value);
};
// объединенный конфиг
class Config {
public:
    CommunicatorConfig* comm;
    TachometrConfig* tacho;
    ChassisConfig* chassis;
    ControlConfig* control;
    void update(const String* name, const char* value);
};

#endif //ROBOCAR_CONFIG_H
