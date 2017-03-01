#include "Akane_Logger.h"

void Akane_Logger::initialize() {
   Serial.begin(SERIAL_BAUD_RATE);
}

void Akane_Logger::log(const String &msg) {
  if(DEBUG_AKANE == 1)
    Serial.println(msg);
}
