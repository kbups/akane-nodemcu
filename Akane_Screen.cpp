#include "Akane_Screen.h"

Akane_Screen::Akane_Screen() {
  tft = new Adafruit_ILI9341(TFT_CS, TFT_DC);
  
  ip_address_1 = "0.0.0.0";
  ip_address_2 = "0.0.0.0";
}

void Akane_Screen::initialize() { 
  tft->begin();
  tft->setRotation(TFT_ROTATE);
  
  // General
  tft->fillScreen(SCREEN_BGCOLOR);
  
  // Title
  tft->setFont(&Roboto_Light7pt7b);
  tft->setTextColor(SCREEN_TITLECOLOR);
  print_str("Akane", 1, 7, 18);
  
  // Panels
  draw_panel(SCREEN_PANEL1_BGCOLOR, 0, 28, 240, 60);
  draw_panel(SCREEN_PANEL2_BGCOLOR, 0, 88, 120, 60);
  draw_panel(SCREEN_PANEL3_BGCOLOR, 120, 88, 120, 60);
  draw_panel(SCREEN_PANEL4_BGCOLOR, 0, 148, 120, 60);
  draw_panel(SCREEN_PANEL5_BGCOLOR, 120, 148, 120, 60);
  
  // Relays
  tft->setFont(&FreeSans6pt7b);
  
  tft->setTextColor(SCREEN_RELAY_FGHEATER);
  print_str("HEATER", 1, 17, 304);
  update_heater_status(false);
  
  tft->setTextColor(SCREEN_RELAY_FGFAN);
  print_str("FAN", 1, 17, 316);
  update_fan_status(false);

  tft->setTextColor(SCREEN_RELAY_FGMISTING);
  print_str("MISTING", 1, 104, 304);
  update_misting_status(false);
  
  tft->setTextColor(SCREEN_RELAY_FGFOGGER);
  print_str("FOGGER", 1, 104, 316);
  update_fogger_status(false);
  
  tft->setTextColor(SCREEN_RELAY_FGLIGHT);
  print_str("LIGHT", 1, 196, 304);
  update_light_status(false);
}

/** ==============================================================================================
PRINT FUNCTIONS
==============================================================================================  */
void Akane_Screen::print_str(const String &txt, unsigned int size, unsigned int x, unsigned int y) {
	print_str(txt, size, x, y, true);
}

void Akane_Screen::print_str(const String &txt, unsigned int size, unsigned int x, unsigned int y, bool newline) {
  tft->setCursor(x, y);
  print_str(txt, size, newline);
}

void Akane_Screen::print_str(const String &txt, unsigned int size, bool newline) {
	tft->setTextSize(size);
	if(newline) {
		tft->println(txt);
	}
	else {
		tft->print(txt);
	}
}

void Akane_Screen::print_str(unsigned int bg_color, String prev_str, unsigned int fg_color, String str, unsigned int size, unsigned int x, unsigned int y) {
	tft->setTextColor(bg_color);
	print_str(prev_str, size, x, y);
	
	tft->setTextColor(fg_color);
	print_str(str, size, x, y);
}

void Akane_Screen::draw_panel(uint16_t bgcolor, int16_t x, int16_t y, int16_t w, int16_t h) {
  tft->fillRect(x, y, w, h, bgcolor);
}

/** ==============================================================================================
WIFI
==============================================================================================  */
void Akane_Screen::display_wifi_status(bool is_connected, String ip_address, String prev_ip_address) {
	unsigned int color = SCREEN_WIFIACTIVATED;
	if(!is_connected) {
		color = SCREEN_WIFIDEACTIVATED;
	}
	
	tft->fillRect(215, 18, 4, 4,  color);
	tft->fillRect(220, 14, 4, 8,  color);
	tft->fillRect(225, 10, 4, 12, color);
	tft->fillRect(230, 6,  4, 16, color);

	display_ip_addresses(ip_address, ip_address_2);
}

void Akane_Screen::display_wifi_ap_status(String ip_address) {
	if(!wifi_ap_displayed) {
		display_ip_addresses(ip_address_1, ip_address);
		wifi_ap_displayed = true;
	}
}

void Akane_Screen::display_ip_addresses(String ip_address1, String ip_address2) {
  String ip_address_bg = ip_address_1 + " / " + ip_address_2;
  
  ip_address_1 = ip_address1;
  ip_address_2 = ip_address2;
  
  String ip_address_fg = ip_address_1 + " / " + ip_address_2;
  
  tft->setFont(&Roboto_Light6pt7b);
  print_str(SCREEN_BGCOLOR, ip_address_bg, SCREEN_FGCOLOR, ip_address_fg, 1, 55, 18);
}

/** ==============================================================================================
TEMPERATURE
==============================================================================================  */
void Akane_Screen::display_temperature(float temp, float prev_temp) {
	String str_prevtemp = "--";
	if(prev_temp < TEMP_MAXVALUE) {
		str_prevtemp = String(prev_temp, 1);
	}
	
	String str_newtemp = "--";
	if(temp < TEMP_MAXVALUE) {
		str_newtemp = String(temp, 1);
	}
	
	tft->setFont(&Roboto_Light17pt7b);
	print_str(SCREEN_PANEL2_BGCOLOR, str_prevtemp, SCREEN_FGCOLOR, str_newtemp, 1, 50, 128);
}

/** ==============================================================================================
HUMIDITY
==============================================================================================  */
void Akane_Screen::display_humidity(float hum, float prev_hum) {
	String str_prevhum = "--";
	if(prev_hum > 0 && prev_hum < 100) {
		str_prevhum = String(prev_hum, 1);
	}
	
	String str_newhum = "--";
	if(hum > 0 && hum < 100) {
		str_newhum = String(hum, 1);
	}
	
	tft->setFont(&Roboto_Light17pt7b);
	print_str(SCREEN_PANEL3_BGCOLOR, str_prevhum, SCREEN_FGCOLOR, str_newhum, 1, 170, 128);
}

/** ==============================================================================================
WATER LEVEL
==============================================================================================  */
void Akane_Screen::display_waterlevel(float level, float prev_level) {
	String str_prevlevel = "--";
	if(prev_level > 0 && prev_level < 1000) {
		str_prevlevel = String(prev_level, 1);
	}
	
	String str_level = "--";
	if(level > 0 && level < 1000) {
		str_level = String(level, 1);
	}
	
	tft->setFont(&Roboto_Light17pt7b);
	print_str(SCREEN_PANEL4_BGCOLOR, str_prevlevel, SCREEN_FGCOLOR, str_level, 1, 50, 188);
}

/** ==============================================================================================
LIGHT
==============================================================================================  */
void Akane_Screen::display_light(float light, float prev_light) {
	String str_prevlight = "--";
	if(prev_light >= 0 && prev_light <= 100) {
		str_prevlight = String(prev_light, 1);
	}
	
	String str_light = "--";
	if(light >= 0 && light <= 100) {
		str_light = String(light, 1);
	}
	
	tft->setFont(&Roboto_Light17pt7b);
	print_str(SCREEN_PANEL5_BGCOLOR, str_prevlight, SCREEN_FGCOLOR, str_light, 1, 170, 188);
}

/** ==============================================================================================
RELAYS
==============================================================================================  */
void Akane_Screen::update_heater_status(bool is_active) {
  unsigned int color = is_active ? SCREEN_RELAYACTIVATED : SCREEN_RELAYDEACTIVATED;
  tft->fillRect(4, 296, 9, 9, color);
}

void Akane_Screen::update_heater_info(float val) {
  /*tft->fillRect(121, 268, 118, 24, SCREEN_BGCOLOR);
  set_foregroundcolor(SCREEN_PANEL1COLOR);
  print_str(String(val), 1, 130, 286);*/
}

void Akane_Screen::update_fan_status(bool is_active) {
  unsigned int color = is_active ? SCREEN_RELAYACTIVATED : SCREEN_RELAYDEACTIVATED;
  tft->fillRect(4, 308, 9, 9, color);
}

void Akane_Screen::update_fan_info(float val) {
  /*tft->fillRect(121, 294, 118, 24, SCREEN_BGCOLOR);
  set_foregroundcolor(SCREEN_PANEL1COLOR);
  print_str(String(val), 1, 130, 312);*/
}

void Akane_Screen::update_misting_status(bool is_active) {
  unsigned int color = is_active ? SCREEN_RELAYACTIVATED : SCREEN_RELAYDEACTIVATED;
  tft->fillRect(91, 296, 9, 9, color);
}

void Akane_Screen::update_misting_info(float val) {
  /*tft->fillRect(121, 242, 118, 24, SCREEN_BGCOLOR);
  set_foregroundcolor(SCREEN_PANEL1COLOR);
  print_str(String(val), 1, 130, 260);*/
}

void Akane_Screen::update_fogger_status(bool is_active) {
  unsigned int color = is_active ? SCREEN_RELAYACTIVATED : SCREEN_RELAYDEACTIVATED;
  tft->fillRect(91, 308, 9, 9, color);
}

void Akane_Screen::update_light_status(bool is_active) {
  unsigned int color = is_active ? SCREEN_RELAYACTIVATED : SCREEN_RELAYDEACTIVATED;
  tft->fillRect(183, 296, 9, 9, color);
}

/** ==============================================================================================
DATE and TIME
==============================================================================================  */
void Akane_Screen::update_date(short day, short month, short year, short day_of_week) {
  String date = String(day) + "/" + String(month) + "/" + String(year);
  
  tft->setTextColor(SCREEN_FGCOLOR);
  
  tft->setFont(&Roboto_Light12pt7b);
  print_str(date, 1, 72, 77); // 15
}

void Akane_Screen::update_time(short hours, short minutes, short seconds) {
  String time = String(hours) + ":" + String(minutes);// + ":" + String(seconds);
  
  tft->setTextColor(SCREEN_FGCOLOR);
  
  tft->setFont(&Roboto_Light16pt7b);
  print_str(time, 1, 72, 59, false); // 22
  
  tft->setFont(&Roboto_Light22pt7b);
  print_str(":" + String(seconds), 11, true);
}

