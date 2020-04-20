//MASTER
#include <Wire.h>

byte num = 0;

void setup(){
  Wire.begin(); //as master
  Serial.begin(9600);
  Serial.println("START");
}

void loop(){
 
  //richiedo un byte allo slave che ha indirizzo 0x04
  Wire.requestFrom(10, 1);
  
  //attendo la disponibilità di dati sul bus i2c
  while(Wire.available()){
    //quando è presente un dato avvia
    //la lettura
    num = Wire.read();
  }
  
  //incrementa il valore del byte
  Serial.println(char(num));
  
  delay(100);

}
