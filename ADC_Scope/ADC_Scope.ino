#include <stdio.h>
#include <math.h>

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64

#define OLED_RESET 4

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  pinMode(A0, INPUT);
  
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.display();

  delay(1000);
}

void loop() {
  drawGraph();
}

void drawGraph()
{
  display.clearDisplay();
  display.setCursor(0,16);
  
  for(int i=0; i<SCREEN_WIDTH; i++)
  {
    display.drawLine(i,SCREEN_HEIGHT-1,i,SCREEN_HEIGHT-1-(analogRead(A0)/22),WHITE);
  }

  display.display();
  delay(25);
}
