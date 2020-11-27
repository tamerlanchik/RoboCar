#ifdef UNIT_TEST
    #include <car/config.h>
#else
    #include <config.h>
#endif

void Config::update(const String* name, const char* value) {
    if (*name =="t.a") {
        tacho->a = atof(value);
    } else if(*name == "t.win") {
        tacho->winSize = atoi(value);
    } else if(*name == "ch.eps") {
        chassis->epsMov = atof(value);
    }
}