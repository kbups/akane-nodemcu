#include "Akane_Screen.h"

Akane_Screen::Akane_Screen() {
  tft = new Adafruit_ILI9341(TFT_CS, TFT_DC);  
}

void Akane_Screen::initialize() { 
  tft->setFont(&FreeSans9pt7b);
  
  tft->begin();
  tft->setRotation(TFT_ROTATE);

  set_backgroundcolor(SCREEN_BGCOLOR);
  draw_panel(1);

  // Heater
  tft->drawFastHLine(0, 267, 240, ILI9341_WHITE);
  tft->drawFastHLine(0, 293, 240, ILI9341_WHITE);
  tft->drawFastVLine(0, 267, 25, ILI9341_WHITE);
  tft->drawFastVLine(239, 267, 25, ILI9341_WHITE);
  set_foregroundcolor(ILI9341_WHITE);
  print_str("HEATER", 1, 28, 286);
  update_heater_status(false);
  
  // Fan Extractor
  tft->drawFastHLine(0, 293, 240, ILI9341_WHITE);
  tft->drawFastHLine(0, 319, 240, ILI9341_WHITE);
  tft->drawFastVLine(0, 293, 25, ILI9341_WHITE);
  //tft->drawFastVLine(120, 293, 25, ILI9341_WHITE);
  tft->drawFastVLine(239, 293, 25, ILI9341_WHITE);
  set_foregroundcolor(ILI9341_WHITE);
  print_str("FAN EXT.", 1, 28, 312);
  update_fan_status(false);
  
  // Humifier
  tft->drawFastHLine(0, 241, 240, ILI9341_WHITE);
  //tft->drawFastHLine(0, 267, 240, ILI9341_WHITE);
  tft->drawFastVLine(0, 241, 25, ILI9341_WHITE);
  //tft->drawFastVLine(120, 293, 25, ILI9341_WHITE);
  tft->drawFastVLine(239, 241, 25, ILI9341_WHITE);
  set_foregroundcolor(ILI9341_WHITE);
  print_str("HUM.", 1, 28, 260);
  update_hum_status(false);
}

void Akane_Screen::set_backgroundcolor(unsigned int color) {
  tft->fillScreen(color);
}

void Akane_Screen::set_foregroundcolor(unsigned int color) {
  tft->setTextColor(color);
}

void Akane_Screen::draw_panel(unsigned int pos) {
  tft->fillRect(0, 100, 240, 50, SCREEN_PANEL1COLOR);
  set_foregroundcolor(ILI9341_WHITE);
  print_str("Temperature", 1, 10, 135);

  tft->fillRect(0, 160, 240, 50, SCREEN_PANEL2COLOR);
  set_foregroundcolor(ILI9341_WHITE);
  print_str("Humidity", 1, 10, 195);
}

void Akane_Screen::print_str(const String &txt, unsigned int size, unsigned int x, unsigned int y) {
  tft->setCursor(x, y);
  print_str(txt, size);
}

void Akane_Screen::print_str(const String &txt, unsigned int size) {
  tft->setTextSize(size);
  tft->println(txt);
}

void Akane_Screen::print_str(unsigned int bg_color, String prev_str, unsigned int fg_color, String str, unsigned int size, unsigned int x, unsigned int y) {
  set_foregroundcolor(bg_color);
  print_str(prev_str, size, x, y);

  set_foregroundcolor(fg_color);
  print_str(str, size, x, y);
}

void Akane_Screen::display_wifi_status(bool is_connected, String ip_address, String prev_ip_address) {
  unsigned int color = ILI9341_WHITE;
  if(!is_connected) {
    color = ILI9341_RED;
  }
  tft->fillRect(215, 15, 4, 3, color);
  tft->fillRect(220, 12, 4, 6, color);
  tft->fillRect(225, 9, 4, 9, color);
  tft->fillRect(230, 6, 4, 12, color);

  print_str(SCREEN_BGCOLOR, prev_ip_address, ILI9341_WHITE, ip_address, 1, 80, 20);
}

void Akane_Screen::display_wifi_ap_status(String ip_address) {
  if(!wifi_ap_displayed) {
    print_str(SCREEN_BGCOLOR, "", ILI9341_WHITE, ip_address, 1, 80, 40);
    wifi_ap_displayed = true;
  }
}

void Akane_Screen::display_temperature(float temp, float prev_temp) {
  set_foregroundcolor(SCREEN_PANEL1COLOR);
  if(prev_temp >= TEMP_MAXVALUE) {
    print_str("--", 2, 150, 135);
  }
  else {
    print_str(String(prev_temp, 1), 2, 150, 135);
  }

  set_foregroundcolor(SCREEN_PANELTXTCOLOR);
  if(temp >= TEMP_MAXVALUE) {
    print_str("--", 2, 150, 135);
  }
  else {
    print_str(String(temp, 1), 2, 150, 135);
  }
}

void Akane_Screen::display_humidity(float hum, float prev_hum) {
  set_foregroundcolor(SCREEN_PANEL2COLOR);
  if(prev_hum < 0) {
    print_str("--", 2, 150, 195);
  }
  else {
    print_str(String(prev_hum, 1), 2, 150, 195);
  }

  set_foregroundcolor(SCREEN_PANELTXTCOLOR);
  if(hum < 0) {
    print_str("--", 2, 150, 195);
  }
  else {
    print_str(String(hum, 1), 2, 150, 195);
  }
}

void Akane_Screen::update_fan_status(bool is_active) {
  unsigned int color = is_active ? ILI9341_GREEN : ILI9341_RED;
  tft->fillRect(10, 302, 8, 8, color);
}

void Akane_Screen::update_fan_info(float val) {
  tft->fillRect(121, 294, 118, 24, SCREEN_BGCOLOR);
  set_foregroundcolor(SCREEN_PANEL1COLOR);
  print_str(String(val), 1, 130, 312);
}

void Akane_Screen::update_heater_status(bool is_active) {
  unsigned int color = is_active ? ILI9341_GREEN : ILI9341_RED;
  tft->fillRect(10, 276, 8, 8, color);
}

void Akane_Screen::update_heater_info(float val) {
  tft->fillRect(121, 268, 118, 24, SCREEN_BGCOLOR);
  set_foregroundcolor(SCREEN_PANEL1COLOR);
  print_str(String(val), 1, 130, 286);
}

void Akane_Screen::update_hum_status(bool is_active) {
  unsigned int color = is_active ? ILI9341_GREEN : ILI9341_RED;
  tft->fillRect(10, 250, 8, 8, color);
}

void Akane_Screen::update_hum_info(float val) {
  tft->fillRect(121, 242, 118, 24, SCREEN_BGCOLOR);
  set_foregroundcolor(SCREEN_PANEL1COLOR);
  print_str(String(val), 1, 130, 260);
}

void Akane_Screen::update_time(short hours, short minutes, short seconds) {
  //tft->fillRect(1, 50, 240, 50, ILI9341_RED);
  set_foregroundcolor(ILI9341_WHITE);
  print_str(String(hours) + ":" + String(minutes) + ":" + String(seconds), 1, 80, 85);
}

