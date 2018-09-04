#if !defined(HEADERRE)
#define HEADERRE
#include <RF24.h>
#include "Logger.h"

class RadioExtended : public RF24
{
public:
    RadioExtended(unsigned char,unsigned char,const char*,const char*,rf24_datarate_e,rf24_pa_dbm_e,bool);
    bool write(void*,int);
};

#endif
