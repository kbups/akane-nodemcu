#include "Akane_Relay.h"

Akane_Relay::Akane_Relay(int pPin, unsigned int pMin_change_delay) {
  pin = pPin;
  pin_status = false;
  min_change_delay = pMin_change_delay;
  pinMode(pin, OUTPUT);
  
  prev_change = millis();
}

void Akane_Relay::setActive(bool pActive) {
  unsigned long t = millis();

  unsigned long t_delay = 0;
  if(t < prev_change) {
    t_delay = t + (UNSIGNED_LONG_MAX - prev_change);
  }
  else {
    t_delay = t - prev_change;
  }

  if(t_delay >= min_change_delay) {
    Akane_Logger::log("[Akane_Relay][setActive] Delay has been reached: " + String(t_delay) + "/" + String(min_change_delay) + ". Updating relay...");
  
    if(pActive) {
      Akane_Logger::log("[Akane_Relay][setActive] Activate PIN " + String(pin) + "...");
      digitalWrite(pin, HIGH);
    }
    else {
      Akane_Logger::log("[Akane_Relay][setActive] Deactivate PIN " + String(pin) + "...");
      digitalWrite(pin, LOW);
    }

    pin_status = pActive;
    prev_change = millis(); // update last changed date
  }
  else {
    Akane_Logger::log("[Akane_Relay][setActive] Delay has not been reached: " + String(t_delay) + "/" + String(min_change_delay) + ". Nothing to do yet.");
  }
}

bool Akane_Relay::isActive() {
  Akane_Logger::log("[Akane_Relay][isActive] PIN " + String(pin) + " status is " + String(pin_status));
  return pin_status;
}

void Akane_Relay::set_min_delay(unsigned int pMin_change_delay) {
  min_change_delay = pMin_change_delay;
}

void Akane_Relay::update(Akane_Sensor *observable) {
  Akane_Logger::log("[Akane_Relay][update] Changed detected...");
  Akane_Logger::log(String(observable->get_value(), 2));
}

