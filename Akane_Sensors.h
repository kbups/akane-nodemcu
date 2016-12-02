#ifndef _AKANE_SENSORSH_
#define _AKANE_SENSORSH_

#include "Akane_Settings.h"

class Akane_Sensors {

  public:
    Akane_Sensors();

    float read_temperature();
    float read_humidity();
  
};

#endif
