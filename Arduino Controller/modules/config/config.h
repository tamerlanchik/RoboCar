#pragma once
#ifndef HeaderCommonConfig
#define HeaderCommonConfig

#define byte unsigned char
#define DEBUG

enum class Mode{CHKCONN = 2, DEF1};
const char radioAdresses[][5] = {"1PIPE","2PIPE"};
enum class RadioMode {SLAVE, MASTER};
const unsigned int messageDataSize = 3;
class RadioMessage{
  private:
    Mode mMode;
    byte mData[messageDataSize];
  public:
    Mode getMode(){return mMode;}
    void setMode(Mode mode){mMode = mode;}
    byte* getDataArray(){return mData;}
    byte getData(unsigned int index){return mData[index];}
    void setData(byte data[]){
      for(unsigned int i = 0; i < messageDataSize; i++){
        mData[i] = data[i];
      }
    }
    void setData(unsigned char index, byte data){
      if(index < messageDataSize){
        mData[index] = data;
      }
    }
};
#endif
