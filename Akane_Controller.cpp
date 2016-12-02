#include "Akane_Controller.h"

Akane_Controller::Akane_Controller(Akane_Settings* psettings, Akane_Sensor pSensors[]) {
  settings = psettings;
  sensors = pSensors;
  
  ESP8266WebServer server(ESP8266_PORT);
}

void Akane_Controller::initialize() {
  this->connect();
}

void Akane_Controller::connect() {
  // Connect to WiFi network
  WiFi.begin(settings->ssid, settings->ssid_pwd);

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
}

void Akane_Controller::execute() {
  
}

IPAddress Akane_Controller::getLocalIP() {
  if(WiFi.status() == WL_CONNECTED) {
    return WiFi.localIP();
  }
  return nullptr;
}

