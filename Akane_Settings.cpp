#include "Akane_Settings.h"

Akane_Settings::Akane_Settings() {
  
}

/*Akane_Settings::Akane_Settings(const char* pssid, const char* pssid_pwd) {
  ssid = (char *)pssid;
  ssid_pwd = (char *)pssid_pwd;
}*/

void Akane_Settings::initialize(const char* pssid, const char* pssid_pwd) { 
  ssid = (char *)pssid;
  ssid_pwd = (char *)pssid_pwd;
}

void Akane_Settings::load() {
  set_ssid("Livebox-NFP");
  set_ssid_pwd("AD5919656EA749C372132E633D");
  
  set_fan_instruction(22);
  set_heater_instruction(22);
  set_hum_instruction(22);//70);
}

void Akane_Settings::save() {
}

