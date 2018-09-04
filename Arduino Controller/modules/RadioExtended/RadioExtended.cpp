#include "RadioExtended.h"
extern Logger* Log;

RadioExtended::RadioExtended(byte CE, byte CSN, const byte* adr1,
                            const byte* adr2, rf24_datarate_e r,
                            rf24_pa_dbm_e l, RadioModes role):RF24(CE, CSN) {
    begin();
    setDataRate(r);
    setPALevel(l);
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
    Log->d("Radio inited");
  }

bool RadioExtended::write(void* data, int size){
  this->stopListening();
  bool fl = RF24::write(data,size);
  this->startListening();

  lastConnectionTime = millis();

  return fl;
}
