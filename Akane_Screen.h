#ifndef _AKANE_SCREENH_
#define _AKANE_SCREENH_

#include "Akane_Settings.h"
#include <Adafruit_ILI9341.h>
#include <Fonts/FreeSans9pt7b.h>

// http://www.barth-dev.de/online/rgb565-color-picker/
//#define SCREEN_BGCOLOR 0x4024      /* 70,   7,  34 */
#define SCREEN_BGCOLOR    0x2863 /* 40,14,27 */
#define SCREEN_PANELCOLOR 0x7C52 /* 121,137,146 */

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

  public:
    void initialize();
    void set_backgroundcolor(unsigned int color);
    void set_foregroundcolor(unsigned int color);
    void draw_panel(unsigned int pos);
    void print_str(const String &txt, unsigned int size, unsigned int x, unsigned int y);
    void print_str(const String &txt, unsigned int size);
    void display_wifi_status(bool is_connected);

  private:  
};

#endif
