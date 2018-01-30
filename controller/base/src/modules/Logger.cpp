#include "Logger.h"
Logger::Logger(){
  Serial.begin(230400);
  delay(200);
  Serial.println("DEBUG: Init serial");
}
void initSerial(int speed){
  Serial.begin(speed);
  delay(400);
  Serial.println("<font color='#f00'>Init serial</font>");
}
void Logger::write(const char mess[], char mode='i')const
{
  switch(mode)
  {
    case 'i': Serial.print("INFO: "); break;
    case 'd': Serial.print("DEBUG: "); break;
    case 'e': Serial.print("ERROR: "); break;
    default: break;
  }
  Serial.println(mess);
}
void Logger::write(int&  mess, char mode='i')const
{
  Serial.print("TEST: ");
  Serial.println(mess);
}
void Logger::write(char& mess, char mode='i')const
{
  Serial.println(int(mess));
}
void Logger::d(const char mess[])const{
  write(mess, 'd');
}
void Logger::e(const char mess[])const{
  write(mess, 'e');
}
void Logger::i(const char mess[])const{
  write(mess, 'i');
}
