#ifndef _AKANE_LOGGERH_
#define _AKANE_LOGGERH_

#include "Akane_Settings.h"
#include "WString.h"

class Akane_Logger {

  public:
    inline static void initialize() {
      Serial.begin(SERIAL_BAUD_RATE);
    };
    
    static void log(const String &msg) {
      if(DEBUG_AKANE == 1)
        Serial.println(msg);
    };
};

#endif
