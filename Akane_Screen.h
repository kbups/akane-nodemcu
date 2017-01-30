#ifndef _AKANE_SCREENH_
#define _AKANE_SCREENH_

#include "Akane_Settings.h"
#include <Adafruit_ILI9341.h>
#include "fonts/FreeSans6pt7b.h"
#include "fonts/RobotoLight6pt7b.h"
#include "fonts/RobotoLight7pt7b.h"
#include "fonts/RobotoLight12pt7b.h"
#include "fonts/RobotoLight16pt7b.h"
#include "fonts/RobotoLight17pt7b.h"
#include "fonts/RobotoLight22pt7b.h"

// http://www.barth-dev.de/online/rgb565-color-picker/

#define SCREEN_BGCOLOR 0x18E3 			/* HEX: #1e1e1e / RGB565: 0x18E3 */
#define SCREEN_FGCOLOR 0xFFFF			/* HEX: #FFFFFF / RGB565: 0xFFFF */
#define SCREEN_TITLECOLOR 0x4459 		/* HEX: #428bca / RGB565: 0x4459 */

#define SCREEN_WIFIACTIVATED 0xFFFF 	/* HEX: #FFFFFF / RGB565: 0xFFFF */ 
#define SCREEN_WIFIDEACTIVATED 0xF800 	/* HEX: #FF0000 / RGB565: 0xF800 */ 

#define SCREEN_RELAYACTIVATED 0x07EF 	/* HEX: #00FF00 / RGB565: 0x07EF */ 
#define SCREEN_RELAYDEACTIVATED 0xF800 	/* HEX: #FF0000 / RGB565: 0xF800 */ 

#define SCREEN_PANEL1_BGCOLOR 0x64CC	/* HEX: #629862 / RGB565: 0x64CC */
#define SCREEN_PANEL2_BGCOLOR 0x836E	/* HEX: #846d74 / RGB565: 0x836E */
#define SCREEN_PANEL3_BGCOLOR 0x4459	/* HEX: #428bca / RGB565: 0x4459 */
#define SCREEN_PANEL4_BGCOLOR 0xE461	/* HEX: #e28f09 / RGB565: 0xE461 */
#define SCREEN_PANEL5_BGCOLOR 0xAD40	/* HEX: #abaa01 / RGB565: 0xAD40 */

#define SCREEN_RELAY_FGHEATER 0x836E	/* HEX: #846d74 / RGB565: 0x836E */
#define SCREEN_RELAY_FGFAN 0x7A4B		/* HEX: #7e4a5a / RGB565: 0x7A4B */
#define SCREEN_RELAY_FGMISTING 0x0A2F	/* HEX: #09477c / RGB565: 0x0A2F */ 
#define SCREEN_RELAY_FGFOGGER 0x4459	/* HEX: #428bca / RGB565: 0x4459 */
#define SCREEN_RELAY_FGLIGHT 0xAD40		/* HEX: #abaa01 / RGB565: 0xAD40 */


class Akane_Screen {
  private:
    Adafruit_ILI9341* tft;

  public:
    static Akane_Screen& getInstance() {
        static Akane_Screen instance; // Guaranteed to be destroyed.
                                      // Instantiated on first use.
        return instance;
    }
    Akane_Screen();

  private:
    Akane_Screen(Akane_Screen const&);   // Don't Implement
    void operator=(Akane_Screen const&); // Don't implement

    bool wifi_ap_displayed;
	String ip_address_1;
	String ip_address_2;

  public:
    void initialize();
    void draw_panel(uint16_t bgcolor, int16_t x, int16_t y, int16_t w, int16_t h);
    
	void print_str(const String &txt, unsigned int size, unsigned int x, unsigned int y);
	void print_str(const String &txt, unsigned int size, unsigned int x, unsigned int y, bool newline);
    void print_str(const String &txt, unsigned int size, bool newline);
    void print_str(unsigned int bg_color, String prev_str, unsigned int fg_color, String str, unsigned int size, unsigned int x, unsigned int y);
	
    void display_wifi_status(bool is_connected, String ip_address, String prev_ip_address);
    void display_wifi_ap_status(String ip_address);
	
    void display_temperature(float temp, float prev_temp);
    void display_humidity(float hum, float prev_hum);
	void display_waterlevel(float level, float prev_level);
	void display_light(float light, float prev_light);
	
    void update_heater_status(bool is_active);
    void update_heater_info(float val);
    void update_fan_status(bool is_active);
    void update_fan_info(float val);
    void update_misting_status(bool is_active);
    void update_misting_info(float val);
	void update_fogger_status(bool is_active);
	void update_light_status(bool is_active);
	
	void update_date(short day, short month, short year, short day_of_week);
    void update_time(short hours, short minutes, short seconds);
    
  private:
	void display_ip_addresses(String ip_address1, String ip_address2);
};

#endif
