//base
#if !defined(HEADCOM)
#define HEADCOM
#include <RadioExtended.h>
#include <pins.h>
#include <config.h>
#include "Logger.h"
#include <RadioMessage.h>
#include <CarModel.h>
using namespace std;
class Manager{
private:
    RadioExtended* mRadio;
    RadioMessage* mRadioMessage;
    byte mSerialMessage[32];
    unsigned int mSerialMessageLength;
public:
    Manager();
    bool checkRadioConnection(unsigned int);
    RadioMessage* readRadio();
    bool sendCommandRadio(RadioMessage::MC);
    void sendTestLongParcelRadio();
    bool readSerial();
    void retranslateSerialToRadio();
};
#endif
