#include "Controller.h"
#ifdef UNIT_TEST
    #include <modules/Logger/Logger.hpp>
    #include <car/Model/Model.h>
    #include <modules/Communicator/SerialCommunicator.h>
#else
    #include <Logger.hpp>
    #include <Model.h>
    #include "SerialCommunicator.h"
#endif

extern Logger* Log;

extern TachometrConfig tachometrConfig;
extern CommunicatorConfig communicatorConfig;

Controller::Controller(){
//    radio=new RadioExtended(radioCE,radioCSN, radioAdresses[0], radioAdresses[1], RF24_1MBPS, RF24_PA_MAX, 0);
    os.begin();
    chassis = new Chassis();
    chassis->init();
//    mRadioMessage = new RadioMessage();
    mModel = new Model();

    tachometer[0] = new Tachometr(0);
    tachometer[0]->start<0>(INTERRUPT0);

    tachometer[1] = new Tachometr(1);
    tachometer[1]->start<1>(INTERRUPT1);

    os.addTask([]() {
        for (int i = 0; i < 2; i++)
            Tachometr::handleStopFlag(i);
    }, 9);

    comm = new SerialCommunicator(communicatorConfig.baudrate,
            communicatorConfig.cmdCount,
            communicatorConfig.cmdInit,
            communicatorConfig.isTextMode ? Mode::TEXT: Mode::BINARY);
    Log->println('d', "Controller inited");
    Message msg = Message((int)Commands::PING, "Hello, world");
    comm->send(msg);
}
void Controller::testing(){
    long long t = millis();
    while(millis()-t < 4000){
        chassis->setValue(constrain(f(millis(), t), -255, 255), 0);
    }
}

int Controller::f(long long x, long long x0){
    x -= x0;
    if(x >= 0 && x < 980) return (x+40)/4;
    else if(x >= 980 && x < 1200) return 200;
    else if(x >= 1200 && x < 1800) return 0;
    else if(x>= 1800 && x < 2780) return -(x-1800+40)/4;
    else if(x >= 2780 && x< 3000) return -200;
    else return 0;
}

//RadioMessage* Controller::getRadioMessage(){
//    if(!radio->available()){return NULL;}
//    log->d("Message got");
//    int messSize = radio->getDynamicPayloadSize();
//    Serial.println(messSize);
//    radio->read(mRadioMessage, messSize);
//    return mRadioMessage;
//}

//void Controller::handleMessage(RadioMessage* message){
//    if(!message) return;
//    tone(9, 1000, 50);
//    switch(message->getMode()){
//        case RadioMessage::MC::CHKCONN:
//            log->d("Check conn");
//            message->setData(0, '!');
//            radio->write(message, message->getSize());
//            break;
//        case RadioMessage::MC::ANDR_CHK_CONN:
//            log->d("Android check conn");
//            break;
//        case RadioMessage::MC::CHASSIS_COMM:
//            message->inflateChassisCommandPack(mModel->motorValues);
//            Serial.print(mModel->motorValues[0]);
//            Serial.print(" ");
//            Serial.println(mModel->motorValues[1]);
//            chassis->setValue(mModel->motorValues);
//            break;
//        case RadioMessage::MC::DEF1:
//            log->d("Long parcel got");
//            Serial.println((int)message->getData(4));
//            break;
//        default:
//            log->e("Unknown message mode!");
//            Serial.println((int)message->getMode());
//            break;
//    }
//}

int Controller::ping(long int time) {
    Log->println('d', "ping()");
    return 0;
}

Communicator* Controller::getCommunicator() { return comm; }

Tachometr* Controller::getTachometr() {
    return tachometer[0];
}

Chassis* Controller::getChassis() { return chassis; };
