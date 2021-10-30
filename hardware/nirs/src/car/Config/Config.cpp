//#ifdef UNIT_TEST
//    #include <car/config.h>
//#else
////    #include <Config/config.h>
////#include "config.h"
//#endif
#include "Config.h"

// Динамически обновляем конфиг по команде
void Config::update(const String* name, const char* value) {
    if (*name =="t.aV") {
        tacho->aV = atof(value);
    } else if (*name =="t.aA") {
        tacho->aA = atof(value);
    } else if(*name == "t.winV") {
        tacho->winSizeV = atoi(value);
    } else if(*name == "t.winA") {
        tacho->winSizeA = atoi(value);
    } else if(*name == "ch.eps") {
        chassis->epsMov = atof(value);
    } else {
        if(control->update(name, value)) {
            return;
        }
    }
}

bool ControlConfig::update(const String *name, const char *value) {
    if (*name == "ctrl.Kp") {
        Kp = atof(value);
    } else if (*name == "ctrl.Ki") {
        Ki = atof(value);
    } else if(*name == "ctrl.Kd") {
        Kd = atof(value);
    } else if (*name == "ctrl.errAddFactor") {
        errIntegrAddFactor = atof(value);
    } else if (*name == "ctrl.timeIntegrDivider") {
        timeIntegrDivider = pow(10, atoi(value));
    } else if(*name == "ctrl.AngSpFct") {
        wFactor = atof(value);
    } else {
        return false;
    }
    return true;
}