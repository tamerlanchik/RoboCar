//
// Created by andrey on 19.10.2020.
//

#ifndef ROBOCAR_UTILS_H
#define ROBOCAR_UTILS_H

#include <core/controller_interface/IUtils.h>

class Utils : public IUtils{
public:
    Utils(){}
    void sleep(long int millis);
};


#endif // ROBOCAR_UTILS_H
