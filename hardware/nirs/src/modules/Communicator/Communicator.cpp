#include "Communicator.h"

Communicator::Communicator(size_t messages_count, size_t offset) : msg_cnt(messages_count), msg_offset(offset){
    this->listeners = new Vector<Listener*>[messages_count];
}

Status Communicator::addListener(Cmd cmd, Listener* listener) {
    size_t idx = cmd - this->msg_offset;
    if (idx >= this->msg_cnt) {
        return ERROR;
    }
    int alreadySet = this->findListener(cmd, listener);
    if(alreadySet != NOT_FOUND) {
        return OK;
    }
    if (listeners[idx].empty()) {
        Listener** storage = new Listener*[LISTENERS_QUEUE_LEN];
        this->listeners[idx].setStorage(storage, LISTENERS_QUEUE_LEN, 0);
    }
    this->listeners[idx].push_back(listener);
    return OK;
}

// Найти и вернуть индекс слушателя
int Communicator::findListener(Cmd cmd, Listener* listener) {
    size_t idx = cmd - this->msg_offset;
    Vector<Listener*> ls = this->listeners[idx];
    for(size_t i = 0; i < ls.size(); i++) {
        if(ls.at(i) == listener) {
            return i;
        }
    }
    return NOT_FOUND;
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
        (*l)->operator()(msg);
    }
}
