#ifndef HEADER_BYTEARRAY
#define HEADER_BYTEARRAY
#define byte unsigned char
class ByteArray{
  public:
    static void reverseString(byte a[], int l);

    static float getFloatFromByteArray(byte t[], unsigned int start);
    static int getIntFromByteArray(byte t[], unsigned int start);
};

#endif
