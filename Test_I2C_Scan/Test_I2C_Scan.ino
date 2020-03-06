#include <Wire.h>

void setup() {
  Wire.begin();

  Serial.begin(9600);
  while(!Serial);
  Serial.println("I2C Scanner");

}

void loop() {
  byte error, address;
  int nDevice;

  Serial.println("Scanning... ");

  nDevice = 0;
  for(address = 1; address < 127; address++)
  {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0)
    {
      Serial.print("I2C device found at address 0x");
      if (address<16)
        Serial.print("0");
        
      Serial.print(address,HEX);
      Serial.println("  !");
 
      nDevice++;
    }
    else if (error==4)
    {
      Serial.print("Unknown error at address 0x");
      if (address<16)
        Serial.print("0");
      Serial.println(address,HEX);
    }    
  }

  if (nDevice == 0)
    Serial.println("No I2C devices found");
  else
    Serial.println("done");
 
  delay(5000);  

}
