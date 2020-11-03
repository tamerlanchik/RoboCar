#include "Communicator.h"

Communicator::Communicator(size_t messages_count, size_t offset) : msg_cnt(messages_count), msg_offset(offset){
    this->listeners = new Vector<Listener*>[messages_count];
}

int Communicator::addListener(Cmd cmd, Listener* listener) {
    size_t idx = cmd - this->msg_offset;
    if (idx >= this->msg_cnt) {
        return 1;
    }
    size_t alreadySet = this->findListener(cmd, listener);
    if(alreadySet != 0) {
        return 1;
    }
    if (listeners[idx].empty()) {
        Listener** storage = new Listener*[5];
        this->listeners[idx].setStorage(storage, 5, 0);
    }
    this->listeners[idx].push_back(listener);
    Vector<Listener*> v = listeners[idx];
    return 0;
}

size_t Communicator::findListener(Cmd cmd, Listener* listener) {
    size_t idx = cmd - this->msg_offset;
    if (idx>= this->msg_cnt) {
        return 1;
    }
    Vector<Listener*> ls = this->listeners[idx];
    for(size_t i = 0; i < ls.size(); i++) {
        if(ls.at(i) == listener) {
            return i;
        }
    }
    return 0;
}

Listener* Communicator::removeListener(Cmd cmd, Listener* listener) {
    size_t idx = cmd - this->msg_offset;
    int index = this->findListener(cmd, listener);
    if (index == -1) {
        return nullptr;
    }
    this->listeners[idx].remove(index);
    return listener;
}

void Communicator::notifyListener(Cmd cmd, Message& msg) {
    size_t idx = cmd - this->msg_offset;
    if (idx >= this->msg_cnt) {
        return;
    }
    Vector<Listener*> ls = this->listeners[idx];
    for(auto l = ls.begin(); l != ls.end(); ++l) {
        (*l)->Handle(msg);
    }
}
