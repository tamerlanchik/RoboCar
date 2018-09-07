#include "RadioMessage.h"

unsigned char RadioMessage::ML[3] = {0, 1, 3};

RadioMessage::RadioMessage():mMode(MC::EMPTY) {}

RadioMessage::MC RadioMessage::getMode(){return mMode;}

void RadioMessage::setMode(MC mode){mMode = mode;}

byte* RadioMessage::getDataArray(){return mData;}

byte RadioMessage::getData(unsigned int index){return mData[index];}

void RadioMessage::setData(unsigned char index, byte data){
  if(index < maxDataLength){
    mData[index] = data;
  }
}

unsigned int RadioMessage::getSize(){
    return (sizeof(MC) + ML[(unsigned int)mMode] );
}

bool RadioMessage::isRequestMessage(){
  unsigned char mode = (unsigned char) mMode;
  if(mode >=2 && mode <= 2) return true;
  else return false;
}
