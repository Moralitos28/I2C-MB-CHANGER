//BY CARLOS MORALES
//https://www.patreon.com/moralitos28
//
#include <Wire.h>
byte t0 = 0x70;
byte bf = 0x03;
byte t1 = 0x55;
byte t2 = 0xaa;
byte new_add;
byte address;

// I2c addresses on Modern Robotics devices must be divisible by 2, and between 0x7e and 0x10
// Different hardware may have different rules.
// Be sure to read the requirements for the hardware you're using!


void setup()
{
  Wire.begin();
  Serial.begin(9600);
  while (!Serial);             // Leonardo: wait for serial monitor
}


void loop()
{
  byte original = SearchAddress();
  if ( original == byte(0xFF)) {
    Serial.println("ERROR DEVICE NOT FOUND!!!\n Retrying");
    delay(1000);
    return;
  }
  Serial. println(" TO CHANGE ADDRESS TO 0x16 PRESS: 1 ");
  Serial. println(" TO CHANGE TO 0x32 PRESS: 2 ");
  Serial. println(" TO CHANGE TO 0x21 PRESS: ENTER OR 3 ");

  while (!Serial.available()) {}
  int a = Serial.readString().toInt();
  switch (a) {
    case 1:
      new_add = 0x16;
      break;
    case 2:
      new_add = 0x32;
      break;
    default:
      new_add = 0x21;
  }
  Serial.print("COLOR SENSOR I2C CHANGER NEW ADDRESS WILL BE: ");
  Serial.println("0x" + String((new_add), HEX));
  Serial.println("PLESE TPYPE YES TO PROCED: ");
  while (!Serial.available()) {}
  if (Serial.readString() == "YES") {

    Serial.println("OK PROCEDING!");
  } else {
    Serial.println("OK RETRING!!!");

    Serial.println();
    delay(1000);
    return;
  }

  Serial.println("RECORDING THE ADDRESS WAIT 20 SECONDS...");
  for (address = 1; address < 127; address++ )
  {
    byte error;
    Wire.beginTransmission(address);
    Wire.write(t0);
    delay(10);
    Wire.write((new_add * 2));
    Wire.write(t1);
    Wire.write(t2);
    error = Wire.endTransmission();
    delay(2);
  }
  //CHEK THE PROCESS
  Serial.println( "CHEKING THE ADDRESS!!!");
  byte temp = SearchAddress();
  if (temp == byte(0xFF)) { // if address is not valid
    Serial.println("ERROR !!! DEVICE NOT FOUND THE ADDRESS IS : 0x" + String(temp, HEX));
    while (true);
  } else if ( temp == original ) {
    Serial.print("ERROR!!!! DEVICE ADDRESS NOT RECORDED, MAYBE THE ORGINIAL ADDRESS IS THE SAME AS THE NEW ADDRESS, STAY AT: 0x");
    Serial.println(temp, HEX);
    Serial.println("PLEAS TPYPE YES TO RETRY: ");
    while (!Serial.available()) {}
    if (Serial.readString() == "YES") {

      Serial.println("OK RETRING!");
      Serial.println();
      Serial.println();
      return;
    } else {

      Serial.println("\n\n");
      Serial.println("OK BYE!");
      while (true);
    }
  } else {
    Serial.println("\nADDRESS WIRTTED CORRECTLY!!!");
    Serial.println("TYPE YES TO CHANGE A NEW ADDRESS: ");
    while (!Serial.available()) {}
    if (Serial.readString() == "YES") {

      Serial.println("OK RETRING!");
      Serial.println();
      Serial.println();
      return;
    } else {

      Serial.println("\n\n");
      Serial.println("OK BYE!");
      while (true);
    }
  }
  Serial.println("\n\n");
}

byte SearchAddress() {


  byte error, address1;

  Serial.println("Scanning...");

  for (address1 = 1; address1 < 127; address1++ )
  {
    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.
    Wire.beginTransmission(address1);
    error = Wire.endTransmission();

    if (error == 0)
    {
      Serial.print("I2C device found at address 0x");
      if (address < 16)
        Serial.print("0");
      Serial.print(address1, HEX);
      Serial.println("  !");
      return (address1);
    }
    else if (error == 4)
    {
      Serial.print("Unknown error at address 0x");
      if (address1 < 16)
        Serial.print("0");
      return (byte(0xFF));
      Serial.println(address1, HEX);
    }
  }

  Serial.println("No I2C devices found\n");
  return (byte(0xFF));
}
