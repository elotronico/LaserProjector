#include <Arduino.h>

// See LICENSE file for details
// Copyright 2016 Florian Link (at) gmx.de

#include "Laser.h"
#include "Drawing.h"
#include "Cube.h"
#include "Objects.h"
#include "Logo.h"

// Create laser instance (with laser pointer connected to digital pin 5)
Laser laser(5);

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


// currently unused, some more objects
void drawObjects()
{
  int count = 100;
  laser.setScale(2);
  laser.setOffset(0,0);

  for (int i = 0;i<count;i++) Drawing::drawObject(draw_island, sizeof(draw_island)/4);
  for (int i = 0;i<count;i++) Drawing::drawObject(draw_glasses, sizeof(draw_glasses)/4);
  for (int i = 0;i<count;i++) Drawing::drawObject(draw_smoking, sizeof(draw_smoking)/4);
}

// draws text as scroller from right to left
void drawScroller(String s, float scale = 0.5, int offsetY = 2048, int speed = 100)
{
  int charW = Drawing::advance('I'); // worst case: smallest char
  int maxChar = (4096. / (charW * scale) );
  // some senseful max buffer, don't use a very small scale...
  char buffer[100];
  for (int j = 0;j<maxChar;j++) {
    buffer[j] = ' ';
  }
  laser.setOffset(0,offsetY);
  laser.setScale(scale);
  int scrollX = 0;
  for (int c = 0; c < s.length() + maxChar; c++) {
    int currentScroll = Drawing::advance(buffer[0]);
    while (scrollX < currentScroll) {
      long time = millis();
      int x = -scrollX;;
      int y = 0;
      bool somethingDrawn = false;
      for (int i = 0;i<maxChar;i++) {
        if (buffer[i] != ' ') {
          somethingDrawn = true;
        }
        x += Drawing::drawLetter(buffer[i], x, y);
        if (x > 4096 / scale) {
          break;
        }
      }
      if (!somethingDrawn) { scrollX = currentScroll; }
      scrollX += speed / scale;
      long elapsed = millis() - time;
      if (elapsed < 50) { delay(50-elapsed); }

    }
    scrollX -= currentScroll;
    for (int k = 0;k<maxChar-1;k++) {
      buffer[k] = buffer[k+1];
    }
    if (c<s.length()) {
      buffer[maxChar-1] = s[c];
    } else{
      buffer[maxChar-1] = ' ';
    }
  }
}

void loop() {

  drawScroller(String("THIS PROJECT IS AVAILABLE ON INSTRUCTABLES.COM"),0.5,2048,100);
  rotateCube(400);
  drawScroller(String("SOURCE CODE AVAILABLE ON GITHUB!"),0.25,2048,100);

//  drawObjects();
//  jumpingText();
}
