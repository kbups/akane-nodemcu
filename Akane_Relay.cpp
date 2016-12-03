#include "Akane_Relay.h"

Akane_Relay::Akane_Relay(int pPin) {
  pin = pPin;
}

void Akane_Relay::setActive(bool pActive) {
  //
}

bool Akane_Relay::isActive() {
  return true;
}

void Akane_Relay::update(Akane_Sensor *observable) {
  Akane_Logger::log("[Akane_Relay] Changed detected...");
  Akane_Logger::log(String(observable->get_value(), 2));
}

