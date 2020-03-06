#include <stdio.h>

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 32

#define OLED_RESET 4

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

int adc_v, adc_max=0, adc_min=1023;
int graph_val[SCREEN_WIDTH];

void disp(int adcVal, int adcMax, int adcMin)
{
  char buff[32];
  
  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(WHITE);

  display.setCursor(0,0);
  
  sprintf(buff, "ADC:%4d  %4d  %4d", adcVal, adcMax, adcMin);
  display.print(buff);

  display.display();
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.display();
  delay(2000);
  
  display.clearDisplay();

  pinMode(A0, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  char buff[32];

  display.clearDisplay();
  
  for(int i=0; i<SCREEN_WIDTH; i++)
  {
    adc_v = analogRead(A0);
    adc_max = (adc_v>adc_max?adc_v:adc_max);
    adc_min = (adc_v<adc_min?adc_v:adc_min);
  
    sprintf(buff, "ADC:%4d Max:%4d Min:%4d", adc_v, adc_max, adc_min);
    Serial.println(buff);

    disp(adc_v, adc_max, adc_min);

    display.drawFastVLine(i, 31-(int(adc_v/50)), (int(adc_v/50)), WHITE);
    display.display();
  }
}
