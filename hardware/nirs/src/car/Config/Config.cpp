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
    }
}