//MASTER
#include <Wire.h>

#define slaveAdr 0x04


void setup(){
  Wire.begin(); //as master
  Serial.begin(9600);
  Serial.println("START");
}

void loop(){
 
  //richiedo un byte allo slave che ha indirizzo 0x04
  Wire.requestFrom(slaveAdr, 1);
  Serial.println("requested");
  
  //attendo la disponibilità di dati sul bus i2c
  while(Wire.available()){
     Serial.println(Wire.read());
   }
   
  delay(1000);
  
  Wire.beginTransmission(slaveAdr);
  Wire.write('t');
  Wire.endTransmission();
  
  delay(300);


}
