#include "ByteArray.h"

void ByteArray::reverseString(byte a[], int l){
  char t;
  for(int i=0; i<l/2; i++){
        t = a[i];
        a[i] = a[l-i-1];
        a[l-i-1] = t;
    }
}

float ByteArray::getFloatFromByteArray(byte t[], unsigned int start){
  byte o[4];
  for(int i=0; i<4; i++){
    o[i] = t[i+start];
  }
  ByteArray::reverseString(o, 4);
  return *reinterpret_cast<float*>(o);
}

int ByteArray::getIntFromByteArray(byte t[], unsigned int start){
  byte o[4];
  for(int i=0; i<4; i++){
    o[i] = t[i+start];
  }
  ByteArray::reverseString(o, 4);
  return *reinterpret_cast<int*>(o);
}
