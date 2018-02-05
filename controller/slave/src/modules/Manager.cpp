//slave
#include "Manager.h"
//Logger Log(28800);
extern Logger* Log;
Manager::Manager():sensors(), chassis(),reloadRadioTime(0)
{
  radio=new RadioExtended(9, 10, adr1, adr2, RF24_2MBPS, RF24_PA_MIN, false);
  Log->d("Manager inited");
  //Log->d("Init manager");
  //radio->initRadio(adr1, adr2, RF24_1MBPS);
  //Log->d("Init Radio");
}

Message_template Manager::readRadio() {
  if(radio->available()){
    radio->read(&mess, sizeof(mess));
    Log->d("Package receive:");
    switch(mess.mode)
    {
      case 57:
        Log->d("Check connection");
        mess.data[0]='!';
        radio->write(&mess,sizeof(mess));
        break;
      case 74:
        Log->d("Motor command");
        chassis.setValue(mess.data[0],mess.data[1]);
        mess.data[0]=1;
        //radio->write(&mess,sizeof(mess));
        break;
      case 14:
        Log->d("Sensor request");
        sensors.getValue(mess.data);
        radio->write(&mess, sizeof(mess));
        break;
      case 15:
        Log->d("Sensor request");
        sensors.getValue(mess.data);
        radio->write(&mess, sizeof(mess));
        break;
      case 91:
        Log->d("Bip");
        bip();
        break;
      default:
        Log->d("Unknown mode got");
        Log->write(mess.mode, 'd');
        break;
    }
  }
    return mess;
}
bool Manager::radioAvailable(){
    return radio->available();
}
void Manager::writeRadio(int dat){
  Log->d("WriteRadio");
  message[1]=dat;
  radio->write(&message, 6);
}
void Manager::writeRadio(Message_template m)
{
  Log->d("WriteRadio()");
  mess=m;
  radio->write(&mess, sizeof(mess));
}
bool Manager::readControl() {return 0;}

bool Manager::sendCommandRadio() {return 0;}

bool Manager::sendCommandSerial() {return 0;}

bool Manager::devSerialEvent() {return 0;}

void Manager::ascSensors(char number=0)
{
        Log->d("Asc sensors");
        message[0] = SENSOR_REQUEST;
        message[1] = number;
        radio->write(message, sizeof(message));
}
void Manager::bip()const
{

}
