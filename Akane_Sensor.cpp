#include "Akane_Sensor.h"

Akane_Sensor::Akane_Sensor() : Akane_Sensor("UNDEFINED") { }

Akane_Sensor::Akane_Sensor(String name) {
  this->set_name(name);
  this->nbvalues = 1;
}

void Akane_Sensor::set_name(String name) {
  this->name = name;
}

String Akane_Sensor::get_name() {
  return this->name;
}

short int Akane_Sensor::get_nbvalues() {
  return this->nbvalues;
}

void Akane_Sensor::set_nbvalues(short int count) {
  this->nbvalues = count;
}

float Akane_Sensor::get_value() {
  return this->value;
}

float Akane_Sensor::get_value1() {
  return this->value1;
}

