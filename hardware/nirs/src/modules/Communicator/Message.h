#ifndef ROBOCAR_MESSAGE_H
#define ROBOCAR_MESSAGE_H

typedef unsigned char Cmd;
typedef const char* Load;

class Message {
public:
    Message(Cmd=0, Load=nullptr);
    Cmd getCmd();
    void setCmd(Cmd);
    Load getLoad();
    void setLoad(Load);
private:
    Cmd _cmd;
    Load payload;
};


#endif //ROBOCAR_MESSAGE_H
