//base
#if !defined(HEADCOM)
#define HEADCOM
#include <RadioExtended.h>
#include <pins.h>
#include <config.h>
#include "Logger.h"
#include <RadioMessage.h>
using namespace std;
class Manager{
private:
    RadioExtended* mRadio;
    RadioMessage* mRadioMessage;
public:
    Manager();
    bool checkRadioConnection(unsigned int);
    RadioMessage* readRadio();
    bool sendCommandRadio(RadioMessage::MC);
};
#endif
