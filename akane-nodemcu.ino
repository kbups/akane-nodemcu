#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

/** DS1307 **/
/*
#include <pgmspace.h>
#include <Wire.h>
#include <RtcDS1307.h>

#define countof(a) (sizeof(a) / sizeof(a[0]))

RtcDS1307 Rtc;*/

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
Akane_Relay_Fan* relay_fan;
Akane_Relay_Heater* relay_heater;
Akane_Relay_Hum* relay_hum;
Akane_Observer_Temp* observer_temp;
Akane_Observer_Hum* observer_hum;
Akane_Observer_DateTime* observer_datetime;
/*
void printDateTime(const RtcDateTime& dt)
{
    char datestring[20];

    snprintf_P(datestring, 
            countof(datestring),
            PSTR("%02u/%02u/%04u %02u:%02u:%02u"),
            dt.Month(),
            dt.Day(),
            dt.Year(),
            dt.Hour(),
            dt.Minute(),
            dt.Second() );
    Serial.print(datestring);
}*/

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
  sensor_wifi->addObserver(*observer_wifi);
  
  relay_fan = new Akane_Relay_Fan(15, MIN_FAN_CHANGE_DELAY);
  relay_heater = new Akane_Relay_Heater(0, MIN_HEATER_CHANGE_DELAY);
  relay_hum = new Akane_Relay_Hum(0, 15000, 60000);
  observer_temp = new Akane_Observer_Temp();
  observer_hum = new Akane_Observer_Hum();
  observer_datetime = new Akane_Observer_DateTime();
  sensor_am2301->addObserver(*observer_temp);
  sensor_am2301->addObserver(*observer_hum);
  sensor_am2301->addObserver(*relay_fan);
  sensor_am2301->addObserver(*relay_heater);
  sensor_am2301->addObserver(*relay_hum);
  sensor_ds1307->addObserver(*observer_datetime);

//  Akane_Sensor* sensors[1] = { sensor_ds18b20 }; //sensors[0] = sensor_ds18b20;

//  controller = new Akane_Controller(/*settings, */*sensors);
//  controller->initialize();
/*Serial.print("compiled: ");
  Serial.print(__DATE__);
  Serial.println(__TIME__);
Rtc.Begin();
  Wire.begin(4, 5); // SDA=GPIO3, SCL=GPIO1

  RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);
  printDateTime(compiled);
  Serial.println();

  if (!Rtc.IsDateTimeValid()) {
    // Common Cuases:
    //    1) first time you ran and the device wasn't running yet
    //    2) the battery on the device is low or even missing
    Serial.println("RTC lost confidence in the DateTime!");

    // following line sets the RTC to the date & time this sketch was compiled
    // it will also reset the valid flag internally unless the Rtc device is
    // having an issue
    Rtc.SetDateTime(compiled);
  }

  if (!Rtc.GetIsRunning()) {
    Serial.println("RTC was not actively running, starting now");
    Rtc.SetIsRunning(true);
  }

  RtcDateTime now = Rtc.GetDateTime();
  if (now < compiled) {
    Serial.println("RTC is older than compile time!  (Updating DateTime)");
    Rtc.SetDateTime(compiled);
  }
  else if (now > compiled) {
    Serial.println("RTC is newer than compile time. (this is expected)");
  }
  else if (now == compiled) {
    Serial.println("RTC is the same as compile time! (not expected but all is fine)");
  }

  // never assume the Rtc was last configured by you, so
  // just clear them to your needed state
  Rtc.SetSquareWavePin(DS1307SquareWaveOut_Low);*/
}

void loop() {
/*if (!Rtc.IsDateTimeValid()) 
    {
        // Common Cuases:
        //    1) the battery on the device is low or even missing and the power line was disconnected
        Serial.println("RTC lost confidence in the DateTime!");
    }

    RtcDateTime dt = Rtc.GetDateTime();

    printDateTime(dt);
    Serial.println();*/
/*
  char datestring[20];

//RtcDateTime dt = RtcDateTime(__DATE__, __TIME__);
    snprintf_P(datestring, 
            countof(datestring),
            PSTR("%02u/%02u/%04u %02u:%02u:%02u"),
            dt.Month(),
            dt.Day(),
            dt.Year(),
            dt.Hour(),
            dt.Minute(),
            dt.Second() );
            Serial.print("Time:");
    Serial.println(datestring);
  */
  // put your main code here, to run repeatedly:
  sensor_wifi->read_value();
//  sensor_ds18b20->read_value();
  sensor_am2301->read_value();

//  Akane_Screen::getInstance().update_time(8, 10, 30);

   Serial.printf("Heap size: %u\n", ESP.getFreeHeap());
  delay(1000);
}


