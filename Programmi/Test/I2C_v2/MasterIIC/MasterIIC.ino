//MASTER
#include <Wire.h>

#define slaveAdr 0x04

float temperature = 0;
byte data[2];

void setup(){
  Wire.begin(); //as master
  Serial.begin(9600);
  Serial.println("START");
}

void loop(){
 
  //richiedo un byte allo slave che ha indirizzo 0x04
  Wire.requestFrom(slaveAdr, 5);
  Serial.println("requested");
  
  //attendo la disponibilità di dati sul bus i2c
  while(Wire.available()){
     int i = 0;
     data[i] = Wire.read(); // receive a byte as character
     Serial.print("B: ");
     Serial.println(data[i]);
     i++;
   }
   Serial.println((char)data[2]);
  
  int16_t raw = (data[1] << 8) | data[0];
  temperature = (float)raw / 16.0;

  //incrementa il valore del byte
  Serial.println(temperature);
  
  delay(3000);

}
