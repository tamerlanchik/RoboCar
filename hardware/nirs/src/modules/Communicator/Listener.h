//
// Created by andrey on 03.11.2020.
//

#ifndef ROBOCAR_LISTENER_H
#define ROBOCAR_LISTENER_H

#include "Message.h"

class Listener {
public:
//    virtual void Handle(Message&) = 0;
    virtual void operator()(Message&) = 0;
};

// Can wrap lambdas
class ListenerWrapper : public Listener {
private:
    void(*handler)(Message&);
public:
    ListenerWrapper(void(*handler)(Message&)) : handler(handler) {}
    void operator()(Message& msg) {
        handler(msg);
    }
};

#endif //ROBOCAR_LISTENER_H
