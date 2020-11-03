#include "Message.h"

Message::Message(Cmd cmd, Load load) : _cmd(cmd), payload(load) {}

Cmd Message::getCmd() {
    return this->_cmd;
}
void Message::setCmd(Cmd cmd) {
    this->_cmd = cmd;
}
Load Message::getLoad() {
    return this->payload;
}
void Message::setLoad(Load load) {
    this->payload = load;
}