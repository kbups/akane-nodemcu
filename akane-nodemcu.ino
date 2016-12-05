#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

#include "Akane_Settings.h"
#include "Akane_Screen.h"
#include "Akane_Logger.h"
#include "Akane_Sensor.h"
#include "Akane_Sensor_Wifi.h"
#include "Akane_Sensor_DS18B20.h"
#include "Akane_Relay.h"
#include "Akane_Relay_Wifi.h"
#include "Akane_Observer_Temp.h"
#include "Akane_Controller.h"

//#include "Akane_Sensors.h"
//#include "Akane_Relays.h"

/** ESP8266 **/
const char* ssid     = "Livebox-NFP";
const char* password = "AD5919656EA749C372132E633D";

Akane_Settings* settings;
Akane_Controller* controller;
Akane_Sensor_Wifi* sensor_wifi;
Akane_Sensor_DS18B20* sensor_ds18b20;
Akane_Relay_Wifi* relay_wifi;
Akane_Relay* relay_fan;
Akane_Observer_Temp* observer_temp;

void setup() {
  Akane_Logger::initialize();
  Akane_Logger::log("Initializing...");

  settings = new Akane_Settings(ssid, password);

  sensor_wifi = new Akane_Sensor_Wifi("Wifi");
  sensor_ds18b20 = new Akane_Sensor_DS18B20(DHT21_PIN, 0, "ds18b20");

  relay_wifi = new Akane_Relay_Wifi(settings->ssid, settings->ssid_pwd, true);
  sensor_wifi->addObserver(*relay_wifi);
  
  relay_fan = new Akane_Relay(0);
  observer_temp = new Akane_Observer_Temp();
  sensor_ds18b20->addObserver(*relay_fan);
  sensor_ds18b20->addObserver(*observer_temp);

  Akane_Sensor* sensors[1] = { sensor_ds18b20 }; //sensors[0] = sensor_ds18b20;

  controller = new Akane_Controller(/*settings, */*sensors);
  controller->initialize();

  //
  //sensor_wifi->read_value();
  //sensor_ds18b20->read_value();
  //

  Akane_Screen::getInstance().initialize();

  Akane_Screen::getInstance().set_foregroundcolor(ILI9341_WHITE);
  Akane_Screen::getInstance().print_str("Akane", 1, 1, 20);
}

void loop() {
  // put your main code here, to run repeatedly:
  sensor_wifi->read_value();
  sensor_ds18b20->read_value();
  delay(5000);
}


