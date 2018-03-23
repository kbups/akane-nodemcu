#ifndef _AKANE_SETTINGSH_
#define _AKANE_SETTINGSH_

#include <Arduino.h>

#define DEBUG_AKANE 1
#define ESP8266_PORT 80

#define SERIAL_SPEED 115200
#define UNSIGNED_LONG_MAX 4294967295

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
#define TFT_DC 15//5 = GPIO5 = D1, 15 = GPIO15 = D8 
#define TFT_CS 16//1//4 = GPIO4 = D2, 16 = GPIO16 = D0
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
    char* ssid;
    char* ssid_pwd;

    float fan_instruction;
    float heater_instruction;
    float hum_instruction;

    /*float temp_delta;
    float temp_commands[];

    float hum_delta;
    float hum_commands[];*/
  public:
    static Akane_Settings& getInstance() {
        static Akane_Settings instance; // Guaranteed to be destroyed.
                                        // Instantiated on first use.
        return instance;
    };
    
    Akane_Settings() { };

    inline void initialize(const char* pssid, const char* pssid_pwd) { 
      ssid = (char *)pssid;
      ssid_pwd = (char *)pssid_pwd;
    };
    
    char* get_ssid() { return ssid; };
    void set_ssid(char* pSsid) { ssid = pSsid; };
    
    char* get_ssid_pwd() { return ssid_pwd; };
    void set_ssid_pwd(char* pSsid_pwd) { ssid_pwd = pSsid_pwd; };

    float get_fan_instruction() { return fan_instruction; };
    void set_fan_instruction(float pValue) { fan_instruction = pValue; };

    float get_heater_instruction() { return heater_instruction; };
    void set_heater_instruction(float pValue) { heater_instruction = pValue; };

    float get_hum_instruction() { return hum_instruction; };
    void set_hum_instruction(float pValue) { hum_instruction = pValue; };
    
    inline void load() {
      set_ssid("Livebox-NFP");
      set_ssid_pwd("AD5919656EA749C372132E633D");
      
      set_fan_instruction(22);
      set_heater_instruction(22);
      set_hum_instruction(22);//70);
    };
    inline void save() { };
    
  private:
    Akane_Settings(Akane_Settings const&);   // Don't Implement
    void operator=(Akane_Settings const&); // Don't implement
};

#endif
