//base
#include "Controller.h"
//#include <RadioMessage.h>
extern Logger* Log;
Controller::Controller(){
//  mRadio = new RadioExtended(radioCE, radioCSN, radioAdresses[0], radioAdresses[1], RF24_1MBPS, RF24_PA_MAX, 1);
//  mRadioMessage = new RadioMessage();
  pinMode(6, OUTPUT);
  tone(6, 1000, 200);
  #ifdef DEBUG
    Log->d("Init Manager");
  #endif
}


//bool Controller::checkRadioConnection(unsigned int timeout){
//  mRadioMessage->setMode(RadioMessage::MC::CHKCONN);
//  mRadioMessage->setData(0, '?');
//  mRadio->write(mRadioMessage, mRadioMessage->getSize());
//
//  unsigned long startTime=millis();
//  while(millis()-startTime <= timeout) {   //trying to get respond for 10 millis
//    if(mRadio->available()){
//      mRadio->read(mRadioMessage, mRadioMessage->getSize());
//      if(mRadioMessage->getData(0) == '!'){
//        return true;
//      }else{
//        #ifdef DEBUG
//          Log->e("A wrong check answer is got");
//          Serial.println(mRadioMessage->getData(0));
//          return 0;
//        #endif
//        break;
//      }
//    }
//  }
//  Log->e("No check answer");
//  return 0;
//}
//
//RadioMessage* Controller::readRadio() {
//    if(mRadio->available()){
//      #ifdef DEBUG
//        Log->d("Read Radio");
//      #endif
//      mRadio->read(mRadioMessage, mRadioMessage->getSize());
//      #ifdef DEBUG
//        Log->d("Message get:");
//        Log->write((int)(mRadioMessage->getMode()), 'i');
//        for(int i=0; i<3; i++){
//          Log->write(mRadioMessage->getData(i), 'i');
//        }
//      #endif
//    }
//    return mRadioMessage;
}

//bool Controller::sendCommandRadio(RadioMessage::MC mode) {
//  #ifdef DEBUG
//    Log->d("sendCommandRadio");
//  #endif
//  mRadioMessage->setMode(mode);
//  switch(mode){
//    case RadioMessage::MC::CHKCONN:
//      this->checkRadioConnection(10);
//    default:
//      #ifdef DEBUG
//        Log->e("Unknown command mode");
//      #endif
//      return false;
//  }
//  return true;
//}
//
//void Controller::sendTestLongParcelRadio(){
//  mRadioMessage->setMode(RadioMessage::MC::DEF1);
//  mRadioMessage->setData(4, '@');
//  mRadio->write(mRadioMessage, mRadioMessage->getSize());
//}

bool Controller::readSerial(){
  if(Serial.available()){
    tone(6, 2000, 10);
    unsigned int i = 0;
    do{
      if(Serial.available() > 0){
        mSerialMessage[i] = Serial.read();
        if(mSerialMessage[i++] == ';') break;
      }
    }while(i<32);
    this->mSerialMessageLength = i-1;
    //Serial.println(String((char*)mSerialMessage));  //echo
    return true;
  }
  return false;
}

//void Controller::retranslateSerialToRadio(){
//  if(readSerial()){
//    mRadio->write(mSerialMessage, mSerialMessageLength);
//  }
//}
