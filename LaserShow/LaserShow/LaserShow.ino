#include <Arduino.h>
#include "Laser.h"

// See LICENSE file for details
// Copyright 2016 Florian Link (at) gmx.de


// Create laser instance (with laser pointer connected to digital pin 5)
Laser laser(5);

//-------------------------------------------------
//                setup
//-------------------------------------------------
void setup()
{
  laser.init();
}

// draw a circle using sin/cos
void circle() {
  const int scale = 12;
  laser.sendto(SIN(0)/scale, COS(0)/scale);
  laser.on();
  for (int r = 5;r<=360;r+=5)
  {
    laser.sendto(SIN(r)/scale, COS(r)/scale);
  }
  laser.off();
}


//-------------------------------------------------
//                loop
//-------------------------------------------------
void loop() {

  circle();

}
