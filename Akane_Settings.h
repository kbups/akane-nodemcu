#ifndef _AKANE_SETTINGSH_
#define _AKANE_SETTINGSH_

#include <Arduino.h>
#include <ArduinoJson.h>
#include "FS.h"

#define DEBUG_AKANE 1

#define ESP8266_PORT 80

#define SERIAL_SPEED 115200
#define UNSIGNED_LONG_MAX 4294967295

// MQTT
#define MQTT_PORT 1883

// SENSORS
#define AM2301_PIN 2    // GPIO2 / D4
#define DS1307_SDA 4    // GPI04 / D2
#define DS1307_SCL 5    // GPI05 / D1

#define AM2301_INTERVAL 3000
#define DS18B20_INTERVAL 3000

// OUTPUTS
#define RELAY_FAN 0
#define RELAY_TMP 0
#define RELAY_HUM 0
#define RELAY_WAT 0
#define MIN_HEATER_CHANGE_DELAY 5000
#define MIN_FAN_CHANGE_DELAY 3000

// SCREEN
#define TFT_DC 15 // 5 = GPIO5 = D1, 15 = GPIO15 = D8 
#define TFT_CS 16 // 4 = GPIO4 = D2, 16 = GPIO16 = D0
#define TFT_ROTATE 2 // 1 Horizontal (pins on right) / 3 Horizontal (pins on left)

// SERIAL
#define SERIAL_BAUD_RATE 9600

// TEMPERATURE
#define TEMP_MINVALUE 0
#define TEMP_MAXVALUE 85

// HUMIDITY
#define HUM_MINVALUE 0
#define HUM_MAXVALUE 100

class Akane_Settings {
  private:
    String ssid;
    String ssid_pwd;
    String hostname;
    String mqtt_address;
    
  public:
    static Akane_Settings& getInstance() {
        static Akane_Settings instance; // Guaranteed to be destroyed.
                                        // Instantiated on first use.
        return instance;
    };
    
    Akane_Settings() { 
      if(hostname == NULL || hostname.length() == 0) {
        hostname = "Akane";
      }
    };
    
    String get_ssid() { return ssid; };
    void set_ssid(char* pSsid) { ssid = String(pSsid); };
    
    String get_ssid_pwd() { return ssid_pwd; };
    void set_ssid_pwd(char* pSsid_pwd) { ssid_pwd = String(pSsid_pwd); };

    String get_hostname() { return hostname; };
    void set_hostname(char* pHostname) { hostname = String(pHostname); };

    String get_mqtt_address() { return mqtt_address; };
    void set_mqtt_address(char* pAddress) { mqtt_address = String(pAddress); };
    
    inline bool load() {
      /*set_ssid("Livebox-NFP"); // TODO
      set_ssid_pwd("AD5919656EA749C372132E633D"); // TODO
      set_mqtt_address("192.168.1.50"); // TODO
      set_hostname("Akane"); // TODO
save();*/
      if (!SPIFFS.begin()) {
        Serial.println("[Akane_Settings] Failed to mount file system");
        return false;
      }
      else {
        Serial.println("[Akane_Settings] File system has been mounted");
      }
      
      File configFile = SPIFFS.open("/config.json", "r");
      if (!configFile) {
        Serial.println("[Akane_Settings] Failed to open config file");
        return false;
      }
      
      size_t size = configFile.size();
      if (size > 1024) {
        Serial.println("[Akane_Settings] Config file size is too large");
        return false;
      }

      // Allocate a buffer to store contents of the file.
      std::unique_ptr<char[]> buf(new char[size]);

      // We don't use String here because ArduinoJson library requires the input
      // buffer to be mutable. If you don't use ArduinoJson, you may as well
      // use configFile.readString instead.
      configFile.readBytes(buf.get(), size);

      StaticJsonBuffer<200> jsonBuffer;
      JsonObject& json = jsonBuffer.parseObject(buf.get());

      if (!json.success()) {
        Serial.println("[Akane_Settings] Failed to parse config file");
        return false;
      }

      const char* sSsid = json["ssid"];
      set_ssid((char *) sSsid);
      
      const char* sSsidPwd = json["ssid_pwd"];
      set_ssid_pwd((char *) sSsidPwd);
      
      const char* sHostname = json["hostname"];
      set_hostname((char *) sHostname);
      
      const char* sMqttAddress = json["mqtt_address"];
      set_mqtt_address((char *) sMqttAddress);

      Serial.println("[Akane_Settings] Read data from config file:");
      Serial.println("[Akane_Settings] SSIS:         " + get_ssid());
      Serial.println("[Akane_Settings] SSIS_PWD:     " + get_ssid_pwd());
      Serial.println("[Akane_Settings] HOSTNAME:     " + get_hostname());
      Serial.println("[Akane_Settings] MQTT ADDRESS: " + get_mqtt_address());
      
      return true;
    };
    inline bool save() { 
      if (!SPIFFS.begin()) {
        Serial.println("[Akane_Settings] Failed to mount file system");
        return false;
      }
      else {
        Serial.println("[Akane_Settings] File system has been mounted");
      }
      
      StaticJsonBuffer<200> jsonBuffer;
      JsonObject& json = jsonBuffer.createObject();
      json["ssid"]         = get_ssid();
      json["ssid_pwd"]     = get_ssid_pwd();
      json["hostname"]     = get_hostname();
      json["mqtt_address"] = get_mqtt_address();

      File configFile = SPIFFS.open("/config.json", "w");
      if (!configFile) {
        Serial.println("[Akane_Settings] Failed to open config file for writing");
        return false;
      }
      
      json.printTo(configFile);

      Serial.println("[Akane_Settings] Successfully save this data to config file:");
      Serial.println("[Akane_Settings] SSIS:         " + get_ssid());
      Serial.println("[Akane_Settings] SSIS_PWD:     " + get_ssid_pwd());
      Serial.println("[Akane_Settings] HOSTNAME:     " + get_hostname());
      Serial.println("[Akane_Settings] MQTT ADDRESS: " + get_mqtt_address());
      
      return true;  
    };
    
  private:
    Akane_Settings(Akane_Settings const&); // Don't Implement
    void operator=(Akane_Settings const&); // Don't implement
};

#endif
