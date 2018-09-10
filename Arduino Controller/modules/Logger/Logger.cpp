#include "Logger.h"
Logger::Logger(){
  Serial.begin(115200);
  delay(200);
  Serial.println("DEBUG: Init serial");
}

void Logger::write(const void* mess, char mode, char level){
  switch(level)
  {
    case 'i': Serial.print("I: "); break;
    case 'd': Serial.print("D: "); break;
    case 'e': Serial.print("E: "); break;
    default: break;
  }
  switch(mode)
  {
    case 'd': Serial.println(*((int*)mess));break;
    case 'c': Serial.println(*((char*)mess)); break;
    case 's': Serial.println((char*)mess); break;
    case 'b': Serial.println(*((bool*)mess)); break;
    case 'l': Serial.println(*((double*)mess)); break;
    case 'L': Serial.println(*((unsigned long*)mess)); break;
    default: break;
  }
}

void Logger::d(const void* mess, char mode){
  write(mess, mode, 'd');
}

void Logger::e(const void* mess, char mode){
  write(mess, mode, 'e');
}

void Logger::i(const void* mess, char mode){
  write(mess, mode, 'i');
}
