#if !defined(HEADERLOG)
#define HEADERLOG
#include <Arduino.h>
/*
Log modes (Android Log):
d: DEBUG
e: ERROR
i: INFO


*/
class Logger
{
public:
  Logger();
  void write(const void*,char='s', char ='i');
  void d(const void*,char='s');
  void e(const void*,char='s');
  void i(const void*,char='s');
};

#endif
