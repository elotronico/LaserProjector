#include <Arduino.h>

// See LICENSE file for details
// Copyright 2016 Florian Link (at) gmx.de

#include "Laser.h"


// Create laser instance (with laser pointer connected to digital pin 5)
Laser miLaser(5);

void setup()
{
  miLaser.init();
}

// draw a circle using sin/cos
void circle() {
  const int scale = 12;
  miLaser.sendto(SIN(0)/scale, COS(0)/scale);
  miLaser.on();
  for (int r = 5;r<=360;r+=5)
  {
    miLaser.sendto(SIN(r)/scale, COS(r)/scale);
  }
  miLaser.off();
}



void loop() {

  circle(); 


//  drawObjects();
//  jumpingText();
}
