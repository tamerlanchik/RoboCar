#ifndef ROBOCAR_COMMUNICATOR_H
#define ROBOCAR_COMMUNICATOR_H

#include "Listener.h"
#include "Message.h"
#ifdef UNIT_TEST
    #include <Vector/src/Vector.h>
#else
    #include <Vector.h>
#endif

/*
 * базовый класс коммуникации.
 * Предоставляет интерфейс чтения-записи
 * и функционал слушателей событий.
 */

typedef int Status;
enum {NOT_FOUND=-1, OK, ERROR};
// для каждой команды заводим массив слушателей такого размера
const size_t LISTENERS_QUEUE_LEN = 2;

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

    int findListener(Cmd, Listener*);
};

#endif //ROBOCAR_COMMUNICATOR_H
