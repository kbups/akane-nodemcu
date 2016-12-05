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

  tft->fillRect(0, 190, 240, 50, SCREEN_PANEL2COLOR);
  set_foregroundcolor(ILI9341_WHITE);
  print_str("Humidity", 1, 10, 225);
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

void Akane_Screen::display_temperature(float temp, float prev_temp) {
  set_foregroundcolor(SCREEN_PANEL1COLOR);
  if(prev_temp == TEMP_NOVALUE) {
    print_str("-- °", 2, 150, 135);
  }
  print_str(String(prev_temp, 1) + "°", 2, 150, 135);

  set_foregroundcolor(SCREEN_PANELTXTCOLOR);
  if(temp == TEMP_NOVALUE) {
    print_str("-- °", 2, 150, 135);
  }
  print_str(String(temp, 1) + "°", 2, 150, 135);
}

