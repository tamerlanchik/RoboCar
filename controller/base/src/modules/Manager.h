#if !defined(HEADCOM)
#define HEADCOM
#include "RadioExtended.h"
#include "Joysticks.h"
#include "Indication.h"
#include "pins.h"
//#include "Logger.h"
class Manager{
private:
    int motorVals[2];
    int sonarAngle;
    bool isScanningFlag;
    bool isSignallingFlag;
    bool isMovingFlag;
    int sensorData[3];
    int urgentData[3];
    char message[3];
    Indication indicator;
    Joysticks control;
    RadioExtended radio;
    int i=0;
    enum messageCodes {MOTOR_COMMAND, SENSOR_REQUEST, ACCOUNT_REQUEST, TEST1};
public:
    Manager();
    void init();
    bool readRadio();
    bool radioAvailable();
    bool readControl();
    bool setIndication(int);
    void sendTest();
    bool sendCommandRadio();
    bool sendCommandSerial();
    void devSerialEvent();
    void ascSensors(char);
};
#endif
