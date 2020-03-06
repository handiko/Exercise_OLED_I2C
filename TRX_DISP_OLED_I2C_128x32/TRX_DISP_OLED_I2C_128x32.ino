#include <math.h>
#include <stdio.h>

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 32

#define OLED_RESET 4
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define TXRX_OFFSET 95

void disp(int freq, bool catStatus, bool txStatus)
{
  char buff[16];

  display.clearDisplay();
  
  display.setTextSize(2);
  display.setTextColor(WHITE);
  
  display.setCursor(0,0);
  if(freq < 10000)
    sprintf(buff, "VFO: %d.%03d", freq/1000, freq%1000);
  else
    sprintf(buff, "VFO:%d.%03d", freq/1000, freq%1000);

  display.print(buff);

  display.setCursor(0,SCREEN_HEIGHT/2 + 2);
  if(catStatus)
    display.print("CAT OK"); 
  else
    display.print("CAT(!)"); 

  display.setCursor(TXRX_OFFSET, SCREEN_HEIGHT/2 + 2);
  if(txStatus)
    display.print("TX"); 
  else
    display.print("RX");
  
  display.display();
}

void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
}

void loop() {
  disp(21074, true, false);
}
