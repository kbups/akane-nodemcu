#include "Akane_Sensor.h"

Akane_Sensor::Akane_Sensor() {
  this->set_name("UNDEFINED");
}

Akane_Sensor::Akane_Sensor(String name) {
  this->set_name(name);
}

void Akane_Sensor::set_name(String name) {
  this->name = name;
}

String Akane_Sensor::get_name() {
  return this->name;
}

float Akane_Sensor::get_value() {
  return this->value;
}

