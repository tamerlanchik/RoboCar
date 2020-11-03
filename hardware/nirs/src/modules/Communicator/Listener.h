//
// Created by andrey on 03.11.2020.
//

#ifndef ROBOCAR_LISTENER_H
#define ROBOCAR_LISTENER_H

#include "Message.h"

class Listener {
public:
    virtual void Handle(Message&) = 0;
};

#endif //ROBOCAR_LISTENER_H
