#if !defined(HEADERRE)
#define HEADERRE
#include <RF24.h>
#include "Logger.h"

class RadioExtended : public RF24
{
public:
    RadioExtended(int,int,const uint8_t*,const uint8_t*,rf24_datarate_e,rf24_pa_dbm_e,bool);
    bool write(void*,int);
};

#endif
