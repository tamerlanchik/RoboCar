#ifndef HEADER_RADIO_MESSAGE
#define HEADER_RADIO_MESSAGE
#include <config.h>
#include <ByteArray.h>

class RadioMessage{
  public:
    enum class MC : unsigned char {EMPTY=0, CHKCONN, ANDR_CHK_CONN, CHASSIS_COMM, DEF1};
  private:
    const static unsigned char maxDataLength = 10;
    static unsigned char ML[5];

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
    void inflateChassisCommandPack(int[]);
};

#endif
