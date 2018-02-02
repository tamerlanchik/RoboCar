//base
#if !defined(HEADCOM)
#define HEADCOM
#include "RadioExtended.h"
#include "Joysticks.h"
#include "Indication.h"
#include "pins.h"
#include "Logger.h"
class Manager{
private:
    int motorVals[2];
    int sonarAngle;
    bool isScanningFlag;
    bool isSignallingFlag;
    bool isMovingFlag;
    int sensorData[3];
    int urgentData[3];
    int message[3];
    RadioExtended radio;
    Indication indicator;
    Joysticks control;
    Message_template mess;
    int indicationData[7];
    int i;
    long int time2, timeCheckJoys;
    bool connectionState;
    long int timeConnection;
    int test[2];

public:
    Manager();
    bool checkRadioConnection(int,int);
    bool makeRadioConnection(bool=false);
    bool isConnectionActive();
    void testAscPayloads();
    //bool readRadio();
    Message_template readRadio();
    void writeRadio(Message_template);
    bool radioAvailable();
    bool readControl()const;
    bool setIndication(int);
    void sendTest();
    bool sendCommandRadio();
    bool sendCommandSerial();
    bool devSerialEvent();
    void ascControl();
    void ascSensors(char);
    void printLCD(const char[]);
};
#endif
