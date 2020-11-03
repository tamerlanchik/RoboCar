#include "RadioExtended.h"
extern Log* log;

RadioExtended::RadioExtended(unsigned char CE, unsigned char CSN, const char* adr1,
                            const char* adr2, rf24_datarate_e r,
                            rf24_pa_dbm_e l, bool role):RF24(CE, CSN) {
    begin();
    setDataRate(r);
    setPALevel(l);
    enableDynamicPayloads();
    setRetries(3, 3);

    //role: 1-base, 0-slave
    if(role){
      this->openReadingPipe(1,*adr2);
      this->openWritingPipe(*adr1);
    }else{
      this->openReadingPipe(1,*adr1);
      this->openWritingPipe(*adr2);
    }

    this->startListening();
    #ifdef DEBUG
      log->d("Radio inited");
    #endif
  }

bool RadioExtended::write(void* data, int size){
  this->stopListening();
  bool fl = RF24::write(data,size);
  this->startListening();
  return fl;
}
