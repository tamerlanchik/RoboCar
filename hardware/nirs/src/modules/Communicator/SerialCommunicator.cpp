//
// Created by andrey on 03.11.2020.
//

#include "SerialCommunicator.h"
//#define UNIT_TEST
//#ifdef UNIT_TEST
//    #include "SerialMock.h"
//    SerialMock serial = SerialMock();
//#else
//    #import <Arduino.h>
//    #define serial Serial
//#endif

SerialCommunicator::SerialCommunicator(int baudrate, size_t messages_count, size_t offset, Mode mode) : Communicator(messages_count, offset), mode(mode), buffer_size(0) {
#ifdef UNIT_TEST
    serial_ = new SerialMock();
    SerialMock serial = *serial_;
#endif
    // It is meant to Log be init
//    serial.begin(baudrate);
    serial.println("Communicator init!");
}

Status SerialCommunicator::send(Message& msg) {
    if (mode == Mode::TEXT) {
#ifdef UNIT_TEST
        SerialMock serial = serial_ ? *serial_ : SerialMock();
#endif
        serial.print((const char)msg.getCmd());
        serial.print("|");
        serial.print(msg.getLoad());
        serial.println("$");
        return 1;
    } else if (mode == Mode::BINARY) {
//        TODO
    }
    return 0;
}
Message SerialCommunicator::get(Cmd cmd) {
    return Message();
}
Message SerialCommunicator::read(bool notify) {
#ifdef UNIT_TEST
    SerialMock serial = serial_ ? *serial_ : SerialMock();
#endif
    while(serial.available() > 0){
        Message msg = Message();
        this->buffer_size = -1;
        // получаем код команды
        int iters = 0;
        do{
            if(serial.available() > 0){
                int res =  serial.read();
                if (res == -1 || res == '$') {
                    continue;
                }
                if (res == '\n') {
                    return msg;
                }
                if (iters == 0) {
                    msg.setCmd(res);
                }
                iters++;
            }
        }while(iters < 2);

        // получаем полезные данные
        do{
            if(serial.available() > 0){
                int res =  serial.read();
                if (res == -1) {
                    continue;
                }
                if (res == '$' or res == '\n') {
                    break;
                }
                this->buffer[++this->buffer_size] = res;
            }
        }while(this->buffer_size < BUFFER_SIZE - 1);
        this->buffer[++this->buffer_size] = '\0';
        msg.setLoad(this->buffer);
        if (notify) {
            this->notifyListener(msg.getCmd(), msg);
        }
        return msg;
    }
    return Message();
}