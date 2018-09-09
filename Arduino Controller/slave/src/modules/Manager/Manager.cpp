//slave
#include "Manager.h"
extern Logger* Log;

Manager::Manager(){
  radio=new RadioExtended(radioCE,radioCSN, radioAdresses[0], radioAdresses[1], RF24_1MBPS, RF24_PA_MAX, 0);
  chassis = new Chassis();
  chassis->init();
  mRadioMessage = new RadioMessage();
  Log->d("Manager inited");
}
void Manager::testing(){
  long long t = millis();
  while(millis()-t < 4000){
    chassis->setValue(constrain(f(millis(), t), -255, 255), 0);
  }
}

int Manager::f(long long x, long long x0){
  x -= x0;
  if(x >= 0 && x < 980) return (x+40)/4;
  else if(x >= 980 && x < 1200) return 200;
  else if(x >= 1200 && x < 1800) return 0;
  else if(x>= 1800 && x < 2780) return -(x-1800+40)/4;
  else if(x >= 2780 && x< 3000) return -200;
  else return 0;
}

RadioMessage* Manager::getRadioMessage(){
  if(!radio->available()){return NULL;}
  Log->d("Message got");
  int messSize = radio->getDynamicPayloadSize();
  Serial.println(messSize);
  radio->read(mRadioMessage, messSize);
  return mRadioMessage;
}

void Manager::handleMessage(RadioMessage* message){
  if(!message) return;
  switch(message->getMode()){
    case RadioMessage::MC::CHKCONN:
      Log->d("Check conn");
      message->setData(0, '!');
      radio->write(message, message->getSize());
      break;
    case RadioMessage::MC::ANDR_CHK_CONN:
      Log->d("Android check conn");
      break;
    case RadioMessage::MC::DEF1:
      Log->d("Long parcel got");
      Serial.println((int)message->getData(4));
      break;
    default:
      Log->e("Unknown message mode!");
      Serial.println((int)message->getMode());
      break;
  }
}
