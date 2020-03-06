#include <ft857d.h>

#include <stdio.h>

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 32

#define OLED_RESET 4

#define TXRX_OFFSET 95

// radio modes
#define MODE_LSB 0x00
#define MODE_USB 0x01
#define MODE_CW 0x02

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
ft857d radio = ft857d();

// variables
long freq = 21074000;
bool ptt = false;
bool splitActive = false;
bool vfoAActive = true;
byte mode = MODE_USB;

void checkTxStatus()
{
  ptt = (1 ^ digitalRead(7));
  digitalWrite(LED_BUILTIN, ptt);
}

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
    display.print("CAT");  

  display.setCursor(0,SCREEN_HEIGHT/2 + 2);
  if(!txStatus)
    display.print("        Rx"); 
  else
    display.print("    Tx");
  
  display.display();
}

void catGoPtt(bool pttf) {
    // the var ptt follows the value passed, but you can do a few more thing here
    ptt = pttf;

    digitalWrite(LED_BUILTIN, ptt);

    #if defined (DEBUG)
    // debug
    Serial.print("PTT Status is: ");
    Serial.println(ptt);
    #endif
}

// function to pass the TX status
byte catGetTXStatus() {
    /*
     * this must return a byte in wich the different bits means this:
     * 0b abcdefgh
     *  a = 0 = PTT off
     *  a = 1 = PTT on
     *  b = 0 = HI SWR off
     *  b = 1 = HI SWR on
     *  c = 0 = split on
     *  c = 1 = split off
     *  d = dummy data
     *  efgh = PO meter data
     */

    #if defined (DEBUG)
    // debug
    Serial.println("Asked for TX status");
    #endif

    // you have to craft the byte from your data, we will built it from
    // our data
    byte r = 0;
    // we fix the TX power to half scale (8)
    r = ptt<<7 + splitActive<<5 + 8;

    return r;
}

// function to set a freq from CAT
void catSetFreq(long f) {
    // the var freq follows the value passed, but you can do a few more thing here
    freq = f;

    #if defined (DEBUG)
    // debug
    Serial.print("Active VFO freq is: ");
    Serial.println(freq);
    #endif
}

// function to pass the freq to the cat library
long catGetFreq() {
    // this must return the freq as an unsigned long in Hz, you must prepare it before

    #if defined (DEBUG)
    // debug
    Serial.println("Asked for freq");
    #endif

    // pass it away
    return freq;
}

/*
// function to run when VFOs A/B are toggled
void catGoToggleVFOs() {
    // here we simply toggle the value
    vfoAActive = !vfoAActive;

    #if defined (DEBUG)
    // debug
    Serial.print("VFO A active?: ");
    Serial.println(vfoAActive);
    #endif
}
*/

// function to set the mode from the cat command
void catSetMode(byte m) {
    // the var mode follows the value passed, but you can do a few more thing here
    mode = m;

    #if defined (DEBUG)
    // debug
    Serial.print("Active VFO mode is: ");
    Serial.println(mode);
    #endif
}

// function to pass the mode to the cat library
byte catGetMode() {
    // this must return the mode in the wat the CAT protocol expect it

    #if defined (DEBUG)
    // debug
    Serial.println("Asked for mode");
    #endif

    // pass it away
    return mode;
}

/*

// function to pass the smeter reading in RX mode
byte catGetSMeter() {
    // this must return a byte in with the 4 LSB are the S meter data
    // so this procedure must take care of convert your S meter and scale it
    // up to just 4 bits

    #if defined (DEBUG)
    // debug
    Serial.println("Asked for S meter");
    #endif

    // pass it away (fixed here just for testing)
    return byte(4);
}
*/

void setup() {
    radio.addCATPtt(catGoPtt);
    radio.addCATTXStatus(catGetTXStatus);
    radio.addCATFSet(catSetFreq);
    radio.addCATGetFreq(catGetFreq);

    //radio.addCATAB(catGoToggleVFOs);
    radio.addCATMSet(catSetMode);
    radio.addCATGetMode(catGetMode);
    //radio.addCATSMeter(catGetSMeter);
    

    // now we activate the library
    radio.begin(57600, SERIAL_8N1);
    //radio.begin();

    #if defined (DEBUG)
    // serial welcome
    Serial.println("CAT Serial Test Ready");
    #endif

    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    display.clearDisplay();

    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(1, INPUT);
    pinMode(7, INPUT);
    digitalWrite(LED_BUILTIN, LOW);
}

void loop() {
    radio.check();
    checkTxStatus();
    disp(freq/1000, (digitalRead(1)==0 ? true:false) , ptt);

    delay(100);
}
