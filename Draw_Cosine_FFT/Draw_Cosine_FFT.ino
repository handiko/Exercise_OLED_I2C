#include "fix_fft.h"
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

const int m=7;
const int tab[]={2,4,8,16,32,64,128};
const int SAMPLES = tab[m-1];
char vReal[SAMPLES];
char vImag[SAMPLES];
const double samplingFrequency = 6000; 
unsigned int sampling_period_us;
unsigned long microseconds;

void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.display();

  analogReference(DEFAULT);
  sampling_period_us = round(1000000*(1.0/samplingFrequency));
  
  delay(1000);
}

void loop() {
  microseconds = micros();
  for(int i=0; i<SAMPLES; i++)
  {
      vReal[i] = analogRead(A0)*128/1024;
      vImag[i] = 0;
      while(micros() - microseconds < sampling_period_us){
        //empty loop
      }
      microseconds += sampling_period_us;
  }

  fix_fft(vReal, vImag, m, false);

  display.clearDisplay();

  drawSpectrum();

  /*
  
  delay(1000);
  
  display.clearDisplay();
  
  for(int i=1; i<200; i++)
    drawFunc1(i/200.0);

  for(int i=1; i<200; i++)
    drawFunc2(i/20.0);
  
  display.display();
  */
}

void drawSpectrum()
{
  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  
  display.setCursor(0,0);
  display.print("FFT bins=");
  display.print(SAMPLES);

  display.setCursor(0,8);
  display.print("Start=0Hz Stop=");
  display.print((int)(samplingFrequency/2));
  display.print("Hz");

  for(int i=0; i<SCREEN_WIDTH; i++)
  {
    display.setCursor(0,16);
    
    int dat=0;

    if(i%2 == 0)
    {
      dat = sqrt(pow(vReal[i/2],2) + pow(vImag[i/2],2));
    }
    else
    {
      dat = ( sqrt(pow(vReal[(i-1)/2],2) + pow(vImag[(i-1)/2],2))
              + sqrt(pow(vReal[(i+1)/2],2) + pow(vImag[(i+1)/2],2)))
              / 2;
    }
    
    display.drawLine( i, SCREEN_HEIGHT-1,
                      i, SCREEN_HEIGHT-1 - dat/2,
                      WHITE);
  }

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

  display.setCursor(0,16);

  for(int i=0; i<SCREEN_WIDTH; i++)
  {
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

  display.setCursor(0,16);

  for(int i=0; i<SCREEN_WIDTH; i++)
  {
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
