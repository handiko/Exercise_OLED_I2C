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
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.display();

  delay(1000);
}

void loop() {
  display.clearDisplay();
  
  for(int i=1; i<200; i++)
    drawFunc1(i/200.0);

  for(int i=1; i<200; i++)
    drawFunc2(i/20.0);

  /*
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);

  for(int16_t i=0; i<256; i++) {
    if(i == '\n') display.write(' ');
    else          display.write(i);
  }
  */
  
  display.display();
}

void drawFunc1(float f_scale)
{
  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);

  display.print("f(x)=24.cos(");
  display.print(f_scale);
  display.print(".x/57,3.sqrt(");
  display.print(f_scale);
  display.print(".x))");

  for(int i=0; i<SCREEN_WIDTH; i++)
  {
    display.setCursor(0,16);
    
    display.drawPixel(
      i,
      -SCREEN_HEIGHT/2*3/4*cos(f_scale * i/57.3 * sqrt(f_scale * i)) + SCREEN_HEIGHT/2 + SCREEN_HEIGHT/8,
      WHITE);

    display.drawPixel(
      i,
      -SCREEN_HEIGHT/2*3/4*sin(f_scale * i/57.3 * sqrt(f_scale * i)) + SCREEN_HEIGHT/2 + SCREEN_HEIGHT/8,
      WHITE);
      
    
  }

  display.display();
}

void drawFunc2(float f_scale)
{
  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);

  display.print("f(x)=24.cos(");
  display.print(f_scale);
  display.print(".x/57,3)");

  for(int i=0; i<SCREEN_WIDTH; i++)
  {
    display.setCursor(0,16);
    
    display.drawPixel(
      i,
      -SCREEN_HEIGHT/2*3/4*cos(f_scale * i/57.3) + SCREEN_HEIGHT/2 + SCREEN_HEIGHT/8,
      WHITE);

    display.drawPixel(
      i,
      -SCREEN_HEIGHT/2*3/4*sin(f_scale * i/57.3) + SCREEN_HEIGHT/2 + SCREEN_HEIGHT/8,
      WHITE);
      
    
  }

  display.display();
}
