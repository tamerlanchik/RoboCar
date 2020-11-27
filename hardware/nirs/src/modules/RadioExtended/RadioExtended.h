#if !defined(HEADERRE)
#define HEADERRE
//#define UNIT_TEST
#ifdef UNIT_TEST
#include <RF24/RF24.h>
#else
#include <RF24.h>
#endif
#include "Logger.hpp"

class RadioExtended : public RF24
{
public:
    RadioExtended(unsigned char,unsigned char,const char*,const char*,rf24_datarate_e,rf24_pa_dbm_e,bool);
    bool write(void*,int);
};

#endif
