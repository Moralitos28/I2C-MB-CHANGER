//BY CARLOS MORALES
//
//
#include <Wire.h>
byte t0 = 0x70;
byte bf = 0x03;
byte t1 = 0x55;
byte t2 = 0xaa;
//THIS IS THE ADDRESS
  // I2c addresses on Modern Robotics devices must be divisible by 2, and between 0x7e and 0x10
  // Different hardware may have different rules.
  // Be sure to read the requirements for the hardware you're using!
byte new_add =  0x42; //CHAGE IT!


byte address = 0x00;
 
void setup()
{
  Wire.begin();
 
  Serial.begin(9600);
  while (!Serial);             // Leonardo: wait for serial monitor
  
  Serial.print("COLOR SENSOR I2C CHANGER PLESE INSERT A HEX DEC TO THE NEW ADDRESS: ");
  Serial.println("0x" + String((new_add*2), HEX));
  if(SearchAddress() == byte(0xFF)){
    Serial.println("ERROR DEVICE NOT FOUND!!!");
    while(true);
  }
  
  
}
 
 
void loop()
{
      Serial.println("RECORDING THE ADDRESS WAIT 20 SECONDS...");  
   for(address = 1; address < 127; address++ )
  {
        byte error;
    Wire.beginTransmission(address);
    Wire.write(t0);
    delay(100);
    Wire.write((new_add*2));
    Wire.write(t1);
    Wire.write(t2);
    error = Wire.endTransmission();
    delay(2);
  }
    Serial.println( "CHEKING THE ADDRESS!!!");
    byte temp = SearchAddress();
    if(temp == byte(0xFF)){
    Serial.println("ERROR !!! DEVICE NOT FOUND THE ADDRESS IS : 0x" + String(temp, HEX));
    while(true);
    } else if ( temp == address ) {
       Serial.println("ERROR DEVICE ADDRESS NOT RECORDED !!!! SORRY");
    }else {
      Serial.println("\n\n\n  ADDRESS WIRTTED CORRECTLY!!!");
    }
    while(true);
}

byte SearchAddress(){
    
  byte error, address1;
  
  Serial.println("Scanning...");

  for(address1 = 1; address1 < 127; address1++ )
  {
    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.
    Wire.beginTransmission(address1);
    error = Wire.endTransmission();
 
    if (error == 0)
    {
      Serial.print("I2C device found at address 0x");
      if (address<16)
        Serial.print("0");
      Serial.print(address1,HEX);
      Serial.println("  !");
      return(address1);
    }
    else if (error==4)
    {
      Serial.print("Unknown error at address 0x");
      if (address1<16)
        Serial.print("0");
              return(byte(0xFF));
      Serial.println(address1,HEX);
    }    
  }
 
    Serial.println("No I2C devices found\n");
    return(byte(0xFF));
}
