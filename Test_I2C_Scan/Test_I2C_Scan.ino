#include <Wire.h>

void scan()
{
  Serial.println("Scanning... ");

  for(byte address = 1; address < 127; address++)
  {
    Wire.beginTransmission(address);

    if (Wire.endTransmission() == 0)
    {
      Serial.print("I2C device found at address 0x");
      if (address<16)
        Serial.print("0");
        
      Serial.print(address,HEX);
      Serial.println("  !");
    }
  }

  Serial.println("done");
}

void setup() {
  Wire.begin();

  Serial.begin(9600);

  while(!Serial);
  
  Serial.println("            ");
  Serial.print("Sketch:   "); Serial.println(__FILE__);
  Serial.print("Uploaded: "); Serial.println(__DATE__);
  Serial.println("            ");
  
  Serial.println("I2C Scanner");

  scan();
  
}

void loop() {
  
}
