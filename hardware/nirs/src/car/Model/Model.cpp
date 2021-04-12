//
// Created by andrey on 03.11.2020.
//
#ifdef UNIT_TEST
#include <modules/Logger/Logger.hpp>
#else
#include <Logger.h>
#endif
#include "Model.h"
//

extern Logger* Log;

Model::Model(){
    velLin[0] = velLin[1] = 0;
    velAn[0] = 0;
    coordGlob[0] = coordGlob[1] = 0;
    motorValues[0] = motorValues[1] = 0;
    Log->println('d', "Model inited()");
}

void Model::setVelLin(int data[]){
    setVelLin(data[0], data[1]);
}
void Model::setVelLin(int x,int y){
    velLin[0] = x; velLin[1] = y;
}
void Model::setVelAn(int vel){
    velAn[0] =  vel;
}
void Model::setCoordGlob(int data[]){
    setCoordGlob(data[0], data[1]);
}
void Model::setCoordGlob(int x, int y){
    coordGlob[0] = x; coordGlob[1] = y;
}
