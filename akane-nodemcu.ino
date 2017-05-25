#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

#include "Akane_Settings.h"
#include "Akane_Screen.h"
#include "Akane_Logger.h"
#include "Akane_Sensor.h"
#include "Akane_Sensor_Wifi.h"
//#include "Akane_Sensor_DS18B20.h"
#include "Akane_Sensor_AM2301.h"
#include "Akane_Sensor_DS1307.h"
#include "Akane_Relay.h"
#include "Akane_Relay_Fan.h"
#include "Akane_Relay_Heater.h"
#include "Akane_Relay_Hum.h"
#include "Akane_Observer_Wifi.h"
#include "Akane_Observer_MQTT.h"
#include "Akane_Observer_Temp.h"
#include "Akane_Observer_Hum.h"
#include "Akane_Observer_DateTime.h"
#include "Akane_Controller.h"

//#include "Akane_Sensors.h"
//#include "Akane_Relays.h"

//Akane_Settings* settings;
Akane_Controller* controller;
Akane_Sensor_Wifi* sensor_wifi;
//Akane_Sensor_DS18B20* sensor_ds18b20;
Akane_Sensor_AM2301* sensor_am2301;
Akane_Sensor_DS1307* sensor_ds1307;
Akane_Observer_Wifi* observer_wifi;
Akane_Observer_MQTT* observer_mqtt;
Akane_Relay_Fan* relay_fan;
Akane_Relay_Heater* relay_heater;
Akane_Relay_Hum* relay_hum;
Akane_Observer_Temp* observer_temp;
Akane_Observer_Hum* observer_hum;
Akane_Observer_DateTime* observer_datetime;

void setup() {
  Akane_Logger::initialize();
  Akane_Logger::log("Initializing...");

  Akane_Settings::getInstance().load();
  
  Akane_Screen::getInstance().initialize();

  sensor_wifi = new Akane_Sensor_Wifi("Wifi");
//  sensor_ds18b20 = new Akane_Sensor_DS18B20(DHT21_PIN, 0, "ds18b20");
  sensor_am2301 = new Akane_Sensor_AM2301(AM2301_PIN, "AM2301");
  sensor_ds1307 = new Akane_Sensor_DS1307("DS1307");

  observer_wifi = new Akane_Observer_Wifi(true);
  observer_mqtt = new Akane_Observer_MQTT();
  sensor_wifi->addObserver(*observer_wifi);
  
  relay_fan = new Akane_Relay_Fan(15, MIN_FAN_CHANGE_DELAY);
  relay_heater = new Akane_Relay_Heater(0, MIN_HEATER_CHANGE_DELAY);
  relay_hum = new Akane_Relay_Hum(0, 15000, 60000);
  observer_temp = new Akane_Observer_Temp();
  observer_hum = new Akane_Observer_Hum();
  observer_datetime = new Akane_Observer_DateTime();
  ///*sensor_am2301*/observer_mqtt->addObserver(*observer_temp);
  ///*sensor_am2301*/observer_mqtt->addObserver(*observer_hum);
  sensor_am2301->addObserver(*relay_fan);
  sensor_am2301->addObserver(*relay_heater);
  sensor_am2301->addObserver(*relay_hum);
  sensor_ds1307->addObserver(*observer_datetime);

//  Akane_Sensor* sensors[1] = { sensor_ds18b20 }; //sensors[0] = sensor_ds18b20;

//  controller = new Akane_Controller(/*settings, */*sensors);
//  controller->initialize();
}

void loop() {
  // put your main code here, to run repeatedly:
  sensor_wifi->read_value();
//  sensor_ds18b20->read_value();
  sensor_am2301->read_value();
  sensor_ds1307->read_value();
  observer_mqtt->read_value();

   Serial.printf("Heap size: %u\n", ESP.getFreeHeap());
  delay(600);
}


