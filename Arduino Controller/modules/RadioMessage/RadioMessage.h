#ifndef HEADER_RADIO_MESSAGE
#define HEADER_RADIO_MESSAGE
#include <config.h>

class RadioMessage{
  public:
    enum class MC : unsigned char {EMPTY=0, CHKCONN, DEF1};
  private:
    const static unsigned char maxDataLength = 10;
    static unsigned char ML[3];

    MC mMode;
    byte mData[maxDataLength];

  public:
    RadioMessage();
    MC getMode();
    void setMode(MC mode);
    byte* getDataArray();
    byte getData(unsigned int index);
    void setData(unsigned char index, byte data);
    unsigned int getSize();
    bool isRequestMessage();
};

#endif
