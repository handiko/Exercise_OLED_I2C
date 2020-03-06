#include <math.h>

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 32

#define OLED_RESET 4
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
}

void loop() {
  display.setTextSize(2);
  display.setTextColor(WHITE);
  
  display.setCursor(0,0);
  display.print("VFO: 7.074"); 

  display.setCursor(0,SCREEN_HEIGHT/2 + 2);
  display.println("Status: RX"); 
  display.display();
}
