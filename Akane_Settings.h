#ifndef _AKANE_SETTINGSH_
#define _AKANE_SETTINGSH_

#include <Arduino.h>

#define ESP8266_PORT 80

#define SERIAL_SPEED 115200

// SENSORS
#define DHT21_PIN  2    // GPIO2 / D4
#define DS1307_SDA 3    // GPIO3 / D9
#define DS1307_SCL 1    // GPIO1 / D10
#define ILI9341_DC 5    // GPI05 / D1
#define ILI9341_CS 4    // GPI04 / D2

// OUTPUTS
#define RELAY_FAN 0
#define RELAY_TMP 0
#define RELAY_HUM 0
#define RELAY_WAT 0

// SCREEN
#define TFT_DC 5
#define TFT_CS 4
#define TFT_ROTATE 2 // 1 Horizontal (pins on right) / 3 Horizontal (pins on left)

// SERIAL
#define SERIAL_BAUD_RATE 9600

// TEMPERATURE
#define TEMP_NOVALUE 85

class Akane_Settings {
  public:
    char* ssid;
    char* ssid_pwd;

    float temp_delta;
    float temp_commands[];

    float hum_delta;
    float hum_commands[];
  public:
    Akane_Settings();
    Akane_Settings(const char* pssid, const char* pssid_pwd);

    void load();
    void save();
};

#endif
