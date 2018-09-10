#ifndef HEADER_CAR_MODEL
#define HEADER_CAR_MODEL

class CarModel{
public:
  int velLin[2];    //linear velocity
  int velAn[1];     //angular velocity
  int coordGlob[2]; //current coordinates of center of local coordinate system in global CS
  int motorValues[2];

  CarModel();
  void setVelLin(int[]);
  void setVelLin(int,int);
  void setVelAn(int);
  void setCoordGlob(int[]);
  void setCoordGlob(int,int);
};

#endif
