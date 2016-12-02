#ifndef _AKANE_RELAYH_
#define _AKANE_RELASH_

#include "Akane_Settings.h"

class Akane_Relay {
  private:
    int pin;
    
  public:
    Akane_Relay(int pPin);
    void setActive(bool pActive);
    bool isActive();
};

#endif
