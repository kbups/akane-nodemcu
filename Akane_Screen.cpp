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
  tft->fillRect(0, 100, 240, 50, SCREEN_PANELCOLOR);

  tft->fillRect(0, 190, 240, 50, SCREEN_PANELCOLOR);
}

void Akane_Screen::print_str(const String &txt, unsigned int size, unsigned int x, unsigned int y) {
  tft->setCursor(x, y);
  print_str(txt, size);
}

void Akane_Screen::print_str(const String &txt, unsigned int size) {
  tft->setTextSize(size);
  tft->println(txt);
}

void Akane_Screen::display_wifi_status(bool is_connected) {
  unsigned int color = ILI9341_WHITE;
  if(!is_connected) {
    color = ILI9341_RED;
  }
  tft->fillRect(215, 15, 4, 3, color);
  tft->fillRect(220, 12, 4, 6, color);
  tft->fillRect(225, 9, 4, 9, color);
  tft->fillRect(230, 6, 4, 12, color);
}
