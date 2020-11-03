//
// Created by andrey on 03.11.2020.
//

#ifndef ROBOCAR_SERIALCOMMUNICATOR_H
#define ROBOCAR_SERIALCOMMUNICATOR_H

#include "Communicator.h"

//#define UNIT_TEST
#ifdef UNIT_TEST
#include "SerialMock.h"
SerialMock* serial_;
#else
#include <Arduino.h>
//Serial* serial = &Serial;
    #define serial Serial
#endif

const size_t BUFFER_SIZE = 1000;

enum class Mode {TEXT, BINARY};

class SerialCommunicator : public Communicator{
public:
    SerialCommunicator(int, size_t, size_t, Mode);

    Status send(Message&);
    Message get(Cmd);
    Message read(bool notify=false);
private:
    Mode mode;
    char buffer[BUFFER_SIZE];
    size_t buffer_size;
};


#endif //ROBOCAR_SERIALCOMMUNICATOR_H
