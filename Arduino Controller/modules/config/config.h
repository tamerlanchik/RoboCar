#ifndef HeaderCommonConfig
#define HeaderCommonConfig

#define byte unsigned char
#define DEBUG

const char radioAdresses[2][] = {"1PIPE","2PIPE"}
enum class RadioMode {SLAVE, MASTER};
const unsigned int messageDataSize = 3;
class RadioMessage{
  private:
    Mode mMode;
    byte mData[messageDataSize];
  public:
    static enum class Mode{CHKCONN = 2, DEF1};
    Mode getMode(){return mMode;}
    void setMode(Mode mode){mMode = mode;}
    byte* getData(){return mData;}
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
