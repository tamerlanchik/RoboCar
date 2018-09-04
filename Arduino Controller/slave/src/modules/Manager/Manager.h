//slave
#if !defined(HEADCOM)
#define HEADCOM
#include "Logger.h"
#include "Chassis.h"
#include <RadioExtended.h>
#include <pins.h>
class Manager{
private:
  RadioExtended* radio;
  Chassis* chassis;
  RadioMessage mRadioMessage;
public:
    Manager();
    void testing();
    int f(long long, long long);
};
#endif
