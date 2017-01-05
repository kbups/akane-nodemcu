#include "Akane_Relay.h"

Akane_Relay::Akane_Relay(int pPin, unsigned int pMin_change_delay_on, unsigned int pMin_change_delay_off) {
  pin = pPin;
  pin_status = false;
  min_change_delay_on = pMin_change_delay_on;
  min_change_delay_off = pMin_change_delay_off;
  pinMode(pin, OUTPUT);
  
  prev_change = millis();
}

void Akane_Relay::setActive(bool pActive) {
    setActive(pActive, false);
}

void Akane_Relay::setActive(bool pActive, bool pForce) {
  unsigned long t = millis();

  unsigned long t_delay = 0;
  if(t < prev_change) {
    t_delay = t + (UNSIGNED_LONG_MAX - prev_change);
  }
  else {
    t_delay = t - prev_change;
  }

  unsigned int min_change_delay = min_change_delay_on;
  if(!pin_status) {
    min_change_delay = min_change_delay_off;
  }

  if(t_delay >= min_change_delay || pForce) {
    Akane_Logger::log("[Akane_Relay][setActive] Delay has been reached: " + String(t_delay) + "/" + String(min_change_delay) + " (force=" + String(pForce) + "). Updating relay...");
  
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

void Akane_Relay::set_min_delays(unsigned int pMin_change_delay_on, unsigned int pMin_change_delay_off) {
  min_change_delay_on = pMin_change_delay_on;
  min_change_delay_off = pMin_change_delay_off;
}

void Akane_Relay::update(Akane_Sensor *observable) {
  Akane_Logger::log("[Akane_Relay][update] Changed detected...");
  Akane_Logger::log(String(observable->get_value(), 2));
}

