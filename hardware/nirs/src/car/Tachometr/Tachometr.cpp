#include "Tachometr.h"

Tachometr::Tachometr(char pin) : dataActual(false), prevData({})  {
//    attachInterrupt(pin, [pin](){
//
//        }, CHANGE);
}

TachoData Tachometr::getData() {
    return TachoData{};
};

void Tachometr::eventListener() {

}

void Tachometr::updateData() {

};