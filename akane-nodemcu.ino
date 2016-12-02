#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

#include "Akane_Settings.h"
#include "Akane_Controller.h"
#include "Akane_Sensors.h"
#include "Akane_Sensor.h"
#include "Akane_Relays.h"
#include "Akane_Screen.h"
#include "Akane_Logger.h"

/** ESP8266 **/
const char* ssid     = "Livebox-NFP";
const char* password = "AD5919656EA749C372132E633D";

Akane_Sensor tempSensor;// = new Akane_Sensor();
Akane_Sensor humSensor;// = new Akane_Sensor();
Akane_Sensor sensors[2] = { tempSensor, humSensor };

Akane_Settings* settings = new Akane_Settings(ssid, password);
Akane_Controller* controller = new Akane_Controller(settings, sensors);

Akane_Screen* screen = new Akane_Screen();

void setup() {
  screen->initialize();
  screen->set_backgroundcolor(SCREEN_BGCOLOR);
  screen->draw_panel(1);
  
  Akane_Logger::initialize();
  Akane_Logger::log("Initializing...");
  controller->initialize();
 
  screen->set_foregroundcolor(ILI9341_WHITE);
  screen->print_str("AKANE by KBUPS", 1, 1, 20);

  screen->print_str(String("IP Address: " + (String)controller->getLocalIP()), 1);
  Akane_Logger::log((String)controller->getLocalIP());
  Akane_Logger::log((String)WiFi.localIP());
  Serial.println(WiFi.localIP());
}

void loop() {
  // put your main code here, to run repeatedly:

}


