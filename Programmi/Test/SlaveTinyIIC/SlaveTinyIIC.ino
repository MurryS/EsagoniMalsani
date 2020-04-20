//SLAVE
#include <Wire.h>

byte x = 0;

void setup(){
  Wire.begin(0x04); //slave address
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);
}

void loop(){
  delay(1000);
}

void receiveEvent(int data){ //if data on bu
  x = Wire.read(); //read IIC
  x++; // do something
}

void requestEvent(){ // master request, slave have to answer
  Wire.write(x); //to master
}
