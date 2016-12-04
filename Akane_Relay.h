#ifndef _AKANE_RELAYH_
#define _AKANE_RELAYH_

#include "Akane_Settings.h"
#include "Akane_Sensor.h"
#include "Akane_Logger.h"
#include "Observer.h"

class Akane_Relay : public Observer<Akane_Sensor> {
  private:
    int pin;
    
  public:
    Akane_Relay(int pPin);
    void setActive(bool pActive);
    bool isActive();
    virtual void update(Akane_Sensor *observable);
};

#endif
