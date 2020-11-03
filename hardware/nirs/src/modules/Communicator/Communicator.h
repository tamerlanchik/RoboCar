//
// Created by andrey on 03.11.2020.
//

#ifndef ROBOCAR_COMMUNICATOR_H
#define ROBOCAR_COMMUNICATOR_H

#include "Listener.h"
#include "Message.h"

#ifdef UNIT_TEST
#include <Vector/src/Vector.h>
#else
#include <Vector.h>
//#include "Vector.h"
#endif

typedef int Status;

class Communicator {
public:
    Communicator(size_t messages_count, size_t offset);
    virtual int addListener(Cmd, Listener*);
    virtual Listener* removeListener(Cmd, Listener*);
    virtual void notifyListener(Cmd, Message&);

    virtual Status send(Message&) = 0;
    virtual Message get(Cmd) = 0;
    virtual Message read(bool notify=false) = 0;
private:
    Vector<Listener*>* listeners;
    size_t msg_cnt;
    size_t msg_offset;

    size_t findListener(Cmd, Listener*);
};

#endif //ROBOCAR_COMMUNICATOR_H
