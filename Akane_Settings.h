#ifndef _AKANE_SETTINGSH_
#define _AKANE_SETTINGSH_

#include <Arduino.h>

#define ESP8266_PORT 80

#define SERIAL_SPEED 115200

// SENSORS
#define AM2301_PIN 2    // GPIO2 / D4
#define DS1307_SDA 3    // GPIO3 / D9
#define DS1307_SCL 1    // GPIO1 / D10
#define ILI9341_DC 5    // GPI05 / D1
#define ILI9341_CS 4    // GPI04 / D2

// OUTPUTS
#define RELAY_FAN 0
#define RELAY_TMP 0
#define RELAY_HUM 0
#define RELAY_WAT 0
#define MIN_HEATER_CHANGE_DELAY 5000
#define MIN_FAN_CHANGE_DELAY 3000

// SCREEN
#define TFT_DC 5
#define TFT_CS 4
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

    short fan_instruction;
    short heater_instruction;
    short hum_instruction;

    /*float temp_delta;
    float temp_commands[];

    float hum_delta;
    float hum_commands[];*/
  public:
    static Akane_Settings& getInstance() {
        static Akane_Settings instance; // Guaranteed to be destroyed.
                                        // Instantiated on first use.
        return instance;
    }
    Akane_Settings();
    //Akane_Settings(const char* pssid, const char* pssid_pwd);

    void initialize(const char* pssid, const char* pssid_pwd);
    
    char* get_ssid() { return ssid; };
    void set_ssid(char* pSsid) { ssid = pSsid; };
    
    char* get_ssid_pwd() { return ssid_pwd; };
    void set_ssid_pwd(char* pSsid_pwd) { ssid_pwd = pSsid_pwd; };

    short get_fan_instruction() { return fan_instruction; };
    void set_fan_instruction(short pValue) { fan_instruction = pValue; };

    short get_heater_instruction() { return heater_instruction; };
    void set_heater_instruction(short pValue) { heater_instruction = pValue; };

    short get_hum_instruction() { return hum_instruction; };
    void set_hum_instruction(short pValue) { hum_instruction = pValue; };
    
    void load();
    void save();
    
  private:
    Akane_Settings(Akane_Settings const&);   // Don't Implement
    void operator=(Akane_Settings const&); // Don't implement
};

#endif
