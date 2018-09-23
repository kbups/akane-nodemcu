#include "Akane_Screen.h"

Akane_Screen::Akane_Screen() {
  tft = new Adafruit_ILI9341(TFT_CS, TFT_DC);
  
  ip_address_1 = "0.0.0.0";
  ip_address_2 = "0.0.0.0";
}

void Akane_Screen::initialize() {
  prev_temp = TEMP_MAXVALUE;
  
  tft->begin();
  tft->setRotation(TFT_ROTATE);
  
  // General
  tft->fillScreen(SCREEN_BGCOLOR);
  
  // Title
  tft->setFont(&Roboto_Light7pt7b);
  tft->setTextColor(SCREEN_TITLECOLOR);
  print_str(Akane_Settings::getInstance().get_hostname(), 1, 7, 18);
  
  // Panels
  draw_panel(SCREEN_PANEL1_BGCOLOR, 0, 28, 240, 60);
  draw_panel(SCREEN_PANEL2_BGCOLOR, 0, 88, 120, 60);
  draw_panel(SCREEN_PANEL3_BGCOLOR, 120, 88, 120, 60);
  draw_panel(SCREEN_PANEL4_BGCOLOR, 0, 148, 120, 60);
  draw_panel(SCREEN_PANEL5_BGCOLOR, 120, 148, 120, 60);

  // Icons
  tft->drawXBitmap(25, 38, days_bits, 40, 40, SCREEN_FGCOLOR);
  tft->drawXBitmap(7, 98, temperature_bits, 40, 40, SCREEN_FGCOLOR);
  tft->drawXBitmap(129, 98, drop_bits, 40, 40, SCREEN_FGCOLOR);
  tft->drawXBitmap(10, 159, water_bits, 40, 40, SCREEN_FGCOLOR);
  tft->drawXBitmap(130, 159, sun_bits, 40, 40, SCREEN_FGCOLOR);

  // Relays
  tft->setFont(&Roboto_Light7pt7b);
  tft->setTextColor(SCREEN_FGCOLOR);
  
  // Heater
  update_heater_status(false);
  print_str("Heater", 1, 60, 235);

  // Misting
  update_misting_status(false);
  print_str("Misting", 1, 60, 260);

  // Light
  update_light_status(false);
  print_str("Light", 1, 60, 285);

  // Fan
  update_fan_status(false);
  print_str("Fan", 1, 180, 235);

  // Fogger
  update_fogger_status(false);
  print_str("Fogger", 1, 180, 260);
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
	print_str(bg_color, prev_str, fg_color, str, size, x, y, true);
}

void Akane_Screen::print_str(unsigned int bg_color, String prev_str, unsigned int fg_color, String str, unsigned int size, unsigned int x, unsigned int y, bool newline) {
  tft->setTextColor(bg_color);
  print_str(prev_str, size, x, y, newline);
  
  tft->setTextColor(fg_color);
  print_str(str, size, x, y, newline);
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
void Akane_Screen::display_temperature(float temp) {
  display_temperature(temp, prev_temp);
  prev_temp = temp;
}

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
void Akane_Screen::display_humidity(float hum) {
  display_humidity(hum, prev_hum);
  prev_hum = hum;
}

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
void Akane_Screen::display_waterlevel(float level) {
  display_waterlevel(level, prev_waterlevel);
  prev_waterlevel = level;
}

void Akane_Screen::display_waterlevel(float level, float prev_level) {
	String str_prevlevel = "--";
	if(prev_level > 0 && prev_level < 1000) {
		str_prevlevel = String(prev_level, prev_level >= 100 ? 0 : 1);
	}
	
	String str_level = "--";
	if(level > 0 && level < 1000) {
		str_level = String(level, level >= 100 ? 0 : 1);
	}
	
	tft->setFont(&Roboto_Light17pt7b);
	print_str(SCREEN_PANEL4_BGCOLOR, str_prevlevel, SCREEN_FGCOLOR, str_level, 1, 50, 188);
}

/** ==============================================================================================
LIGHT
==============================================================================================  */
void Akane_Screen::display_light(float light) {
  display_light(light, prev_light);
  prev_light = light;
}

void Akane_Screen::display_light(float light, float prev_light) {
	String str_prevlight = "--";
	if(prev_light >= 0 && prev_light <= 100) {
		str_prevlight = String(prev_light, prev_light == 100 ? 0 : 1);
	}
	
	String str_light = "--";
	if(light >= 0 && light <= 100) {
		str_light = String(light, light == 100 ? 0 : 1);
	}
	
	tft->setFont(&Roboto_Light17pt7b);
	print_str(SCREEN_PANEL5_BGCOLOR, str_prevlight, SCREEN_FGCOLOR, str_light, 1, 170, 188);
}

/** ==============================================================================================
RELAYS
==============================================================================================  */
void Akane_Screen::update_relay_status(bool is_active, unsigned int x, unsigned int y, unsigned int color) {
  tft->fillRect(x, y, 40, 20, SCREEN_BGCOLOR);

  if(is_active) {
    tft->drawXBitmap(x, y, switch_bg_on_bits, 22, 20, SCREEN_FGCOLOR);  
    tft->drawXBitmap(x+20, y, switch_btn_bits, 20, 20, color); // 20+20 = 40px width
  }
  else  {
    tft->drawXBitmap(x+18, y, switch_bg_off_bits, 22, 20, SCREEN_FGCOLOR); // 18+22 = 40px width
    tft->drawXBitmap(x, y, switch_btn_bits, 20, 20, SCREEN_RELAYDEACTIVATED);
  }
}

void Akane_Screen::update_heater_status(bool is_active) {
  update_relay_status(is_active, 10, 220, SCREEN_PANEL2_BGCOLOR);
}

void Akane_Screen::update_heater_info(float val) {
}

void Akane_Screen::update_fan_status(bool is_active) {
  update_relay_status(is_active, 130, 220, SCREEN_PANEL2_BGCOLOR);
}

void Akane_Screen::update_fan_info(float val) {
}

void Akane_Screen::update_misting_status(bool is_active) {
  update_relay_status(is_active, 10, 245, SCREEN_PANEL3_BGCOLOR);
}

void Akane_Screen::update_misting_info(float val) {
}

void Akane_Screen::update_fogger_status(bool is_active) {
  update_relay_status(is_active, 130, 245, SCREEN_PANEL3_BGCOLOR);
}

void Akane_Screen::update_light_status(bool is_active) {
  update_relay_status(is_active, 10, 270, SCREEN_PANEL5_BGCOLOR);
}

/** ==============================================================================================
DATE and TIME
==============================================================================================  */
void Akane_Screen::update_date(short year, short month, short day, short prev_year, short prev_month, short prev_day) {
  if(year != prev_year || month != prev_month || day != prev_day) {
    String str_month = get_month(month);
    String str_prev_month = get_month(prev_month);
    
    String prev_date = String(prev_day) + " " + str_prev_month + " " + String(prev_year);
    String date = String(day) + " " + str_month + " " + String(year);

    tft->setFont(&Roboto_Light10pt7b);

    tft->setTextColor(SCREEN_PANEL1_BGCOLOR);
    print_str(prev_date, 1, 72, 77); // 10
    
    tft->setTextColor(SCREEN_FGCOLOR);
    print_str(date, 1, 72, 77); // 10
  }
}

String Akane_Screen::get_month(short month) {
  String str_month = "";
  switch(month) {
    case 1: str_month = "Jan."; break;
    case 2: str_month = "Feb."; break;
    case 3: str_month = "Mar."; break;
    case 4: str_month = "Apr."; break;
    case 5: str_month = "May"; break;
    case 6: str_month = "Jun."; break;
    case 7: str_month = "Jul."; break;
    case 8: str_month = "Aug."; break;
    case 9: str_month = "Sep."; break;
    case 10: str_month = "Oct."; break;
    case 11: str_month = "Nov."; break;
    case 12: str_month = "Dec."; break;
  }

  return str_month;
}

void Akane_Screen::update_time(short hour, short minute, short second, short prev_hour, short prev_minute, short prev_second) {
  String str_second = (second < 10 ? "0" : "") + String(second);
  String str_minute = (minute < 10 ? "0" : "") + String(minute);
  String str_hour = (hour < 10 ? "0" : "") + String(hour);
  
  String str_prev_second = (prev_second < 10 ? "0" : "") + String(prev_second);
  String str_prev_minute = (prev_minute < 10 ? "0" : "") + String(prev_minute);
  String str_prev_hour = (prev_hour < 10 ? "0" : "") + String(prev_hour);
  
  bool hourHasChanged = hour != prev_hour;
  bool minHasChanged = minute != prev_minute;
  bool secHasChanged = second != prev_second;
  
  if(hourHasChanged) {
    tft->setFont(&Roboto_Light16pt7b); // 16
    tft->setTextColor(SCREEN_PANEL1_BGCOLOR);
    print_str(str_prev_hour + ":" + str_prev_minute, 1, 72, 59, false);
    
    tft->setFont(&Roboto_Light12pt7b); // 12
    print_str(":" + str_prev_second, 1, true);
  }
  else if(minHasChanged) {
    tft->setFont(&Roboto_Light16pt7b); // 16
    tft->setTextColor(SCREEN_FGCOLOR);
    print_str(str_prev_hour + ":", 1, 72, 59, false);
    
    tft->setTextColor(SCREEN_PANEL1_BGCOLOR);
    print_str(str_prev_minute, 1, false);
    
    tft->setFont(&Roboto_Light12pt7b); // 12
    print_str(":" + str_prev_second, 1, true);
  }
  else if(secHasChanged) {
    tft->setFont(&Roboto_Light16pt7b); // 16
    tft->setTextColor(SCREEN_FGCOLOR);
    print_str(str_prev_hour + ":" + str_prev_minute, 1, 72, 59, false);
    
    tft->setTextColor(SCREEN_PANEL1_BGCOLOR);
    tft->setFont(&Roboto_Light12pt7b); // 12
    print_str(":" + str_prev_second, 1, true);
  }
  
  tft->setTextColor(SCREEN_FGCOLOR);
  tft->setFont(&Roboto_Light16pt7b); // 16
  print_str(str_hour + ":" + str_minute, 1, 72, 59, false);
  tft->setFont(&Roboto_Light12pt7b); // 12
  print_str(":" + str_second, 1, true);
}

