#ifndef _AKANE_LOGGERH_
#define _AKANE_LOGGERH_

#include "Akane_Settings.h"
#include "WString.h"

class Akane_Logger {

  public:
    static void initialize();
    static void log(const String &msg);
  
};

#endif
