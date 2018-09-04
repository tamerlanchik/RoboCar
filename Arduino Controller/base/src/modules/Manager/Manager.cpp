//base
#include "Manager.h"
extern Logger* Log;
Manager::Manager(){
  mRadio = new RadioExtended(radioCE, radioCSN, radioAdresses[0], radioAdresses[1], RF24_1MBPS, RF24_PA_MAX, 1);
  mRadioMessage = new RadioMessage();
  #ifdef DEBUG
    Log->d("Init Manager");
  #endif
}


bool Manager::checkRadioConnection(unsigned int timeout){
  mRadioMessage->setMode(Mode::CHKCONN);
  mRadioMessage->setData(0, '?');
  mRadio->write(mRadioMessage, sizeof(RadioMessage));
  mRadioMessage->setData(0, '&');

  unsigned long startTime=millis();
  while(millis()-startTime <= timeout) {   //trying to get respond for 10 millis
    if(mRadio->available()){
      mRadio->read(mRadioMessage, sizeof(RadioMessage));
      Serial.println(sizeof(RadioMessage));
      if(mRadioMessage->getData(0) == '!'){
        #ifdef DEBUG
          //Log->d("Connecion is active!");
        #endif
        return true;
      }else{
        #ifdef DEBUG
          Log->e("A wrong check answer is got");
          Serial.println(mRadioMessage->getData(0));
          return 0;
        #endif
        break;
      }
    }
  }
  Log->e("No check answer");
  return 0;
}

RadioMessage* Manager::readRadio() {
    if(mRadio->available()){
      #ifdef DEBUG
        Log->d("Read Radio");
      #endif
      mRadio->read(mRadioMessage, sizeof(mRadioMessage));
      #ifdef DEBUG
        Log->d("Message get:");
        Log->write((int)(mRadioMessage->getMode()), 'i');
        for(int i=0; i<3; i++){
          Log->write(mRadioMessage->getData(i), 'i');
        }
      #endif
    }
    return mRadioMessage;
}

bool Manager::sendCommandRadio(Mode mode) {
  #ifdef DEBUG
    Log->d("sendCommandRadio");
  #endif
  mRadioMessage->setMode(mode);
  switch(mode){
    case Mode::CHKCONN:
      this->checkRadioConnection(10);
    default:
      #ifdef DEBUG
        Log->e("Unknown command mode");
      #endif
      return false;
  }
  return true;
}
