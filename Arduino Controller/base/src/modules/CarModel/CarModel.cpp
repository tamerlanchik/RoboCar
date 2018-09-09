#include "CarModel.h"

CarModel::CarModel(){
  velLin[0] = velLin[1] = 0;
  velAn[0] = 0;
  coordGlob[0] = coordGlob[1] = 0;
}

void CarModel::setVelLin(int data[]){
  setVelLin(data[0], data[1]);
}
void CarModel::setVelLin(int x,int y){
  velLin[0] = x; velLin[1] = y;
}
void CarModel::setVelAn(int vel){
  velAn[0] =  vel;
}
void CarModel::setCoordGlob(int data[]){
  setCoordGlob(data[0], data[1]);
}
void CarModel::setCoordGlob(int x, int y){
  coordGlob[0] = x; coordGlob[1] = y;
}
