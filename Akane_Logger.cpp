#include "Akane_Logger.h"

void Akane_Logger::initialize() {
   Serial.begin(SERIAL_BAUD_RATE);
}

void Akane_Logger::log(const String &msg) {
  Serial.println(msg);
}
