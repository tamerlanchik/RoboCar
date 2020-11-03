//base
#if !defined(HEADCOM)
#define HEADCOM
//#include <RadioExtended.h>
#include <car/pins/pins.h>
#include <modules/config/config.h>
#include "modules/Logger/Logger.hpp"
//#include <RadioMessage.h>
using namespace std;
class Controller{
private:
//    RadioExtended* mRadio;
//    RadioMessage* mRadioMessage;
    byte mSerialMessage[32];
    unsigned int mSerialMessageLength;
public:
    Controller();
    bool checkRadioConnection(unsigned int);
//    RadioMessage* readRadio();
//    bool sendCommandRadio(RadioMessage::MC);
    void sendTestLongParcelRadio();
    bool readSerial();
    void retranslateSerialToRadio();
};
#endif
