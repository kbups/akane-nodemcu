#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

#include "Akane_Settings.h"
#include "Akane_Screen.h"
#include "Akane_Logger.h"
#include "Akane_Sensor.h"
#include "Akane_Sensor_DS18B20.h"
#include "Akane_Relay.h"
#include "Akane_Controller.h"

//#include "Akane_Sensors.h"
//#include "Akane_Relays.h"

/** ESP8266 **/
const char* ssid     = "Livebox-NFP";
const char* password = "AD5919656EA749C372132E633D";

Akane_Settings* settings;
Akane_Screen* screen;
Akane_Controller* controller;
Akane_Sensor_DS18B20* sensor_ds18b20;
Akane_Relay *relay_fan;

void setup() {
  Akane_Logger::initialize();
  Akane_Logger::log("Initializing...");

  settings = new Akane_Settings(ssid, password);

  sensor_ds18b20 = new Akane_Sensor_DS18B20(DHT21_PIN, 0, "ds18b20");
  
  relay_fan = new Akane_Relay(0);
  sensor_ds18b20->addObserver(*relay_fan);

  Akane_Sensor* sensors[1] = { sensor_ds18b20 }; //sensors[0] = sensor_ds18b20;

  controller = new Akane_Controller(settings, *sensors);
  controller->initialize();

  // 
  sensor_ds18b20->read_value();
  //
  
  screen = new Akane_Screen();
  screen->initialize();

  screen->set_foregroundcolor(ILI9341_WHITE);
  screen->print_str("AKANE by KBUPS", 1, 1, 20);

  screen->print_str(String("IP Address: " + (String)controller->getLocalIP()), 1);
  screen->print_str(String("Temp: " + (String)sensor_ds18b20->get_value()), 1);
  Akane_Logger::log((String)controller->getLocalIP());
  Akane_Logger::log("Temperature:" + (String)sensor_ds18b20->get_value());
  //Akane_Logger::log();
  
  Serial.println(WiFi.localIP());
}

void loop() {
  // put your main code here, to run repeatedly:

}


