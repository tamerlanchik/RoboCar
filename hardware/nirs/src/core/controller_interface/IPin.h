//
// Created by andrey on 19.10.2020.
//

#ifndef ROBOCAR_DIGITALIN_H
#define ROBOCAR_DIGITALIN_H

class IPin {
public:
    enum class Mode {Output, Input};
    typedef int Code;

//    IPin(Code pin, Mode mode);
    virtual void digitalWrite(bool) = 0;
    virtual bool digitalRead() = 0;
    virtual void analogWrite(float) = 0;
    virtual float analogRead() = 0;
    virtual void reconnect(Code pin, Mode) = 0;
    virtual Mode getMode() = 0;
    virtual Code getCode() = 0;
    virtual ~IPin();
};

#endif //ROBOCAR_DIGITALIN_H
