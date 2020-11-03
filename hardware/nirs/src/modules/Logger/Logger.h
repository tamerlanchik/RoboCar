#if !defined(HEADERLOG)
#define HEADERLOG

//#ifdef UNIT_TEST
//#include <modules/Logger/Serial/Serial.h>
//#endif
/*
Log modes (Android Log):
d: DEBUG
e: ERROR
i: INFO


*/
class Logger
{
public:
    Logger();
    void d(const char*, ...);
    void e(const char*, ...);
    void i(const char*, ...);
private:
//#ifdef UNIT_TEST
//    _Serial serial;
//#endif
};

#endif
