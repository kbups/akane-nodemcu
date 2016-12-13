#include "Akane_Relay.h"

Akane_Relay::Akane_Relay(int pPin) {
  pin = pPin;
  pin_status = false;
  pinMode(pin, OUTPUT);
}

void Akane_Relay::setActive(bool pActive) {
  if(pActive) {
    Akane_Logger::log("[Akane_Relay][setActive] Activate PIN " + String(pin) + "...");
    digitalWrite(pin, HIGH);
  }
  else {
    Akane_Logger::log("[Akane_Relay][setActive] Deactivate PIN " + String(pin) + "...");
    digitalWrite(pin, LOW);
  }

  pin_status = pActive;
}

bool Akane_Relay::isActive() {
  Akane_Logger::log("[Akane_Relay][isActive] PIN " + String(pin) + " status is " + String(pin_status));
  return pin_status;
}

void Akane_Relay::update(Akane_Sensor *observable) {
  Akane_Logger::log("[Akane_Relay][update] Changed detected...");
  Akane_Logger::log(String(observable->get_value(), 2));
}

