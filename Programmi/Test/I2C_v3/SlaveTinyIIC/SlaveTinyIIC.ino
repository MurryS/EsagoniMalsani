#include <TinyWire.h>

#define adr 0x04
#define led_pin 3


void setup() {
  pinMode(led_pin, OUTPUT);
  // config TinyWire library for I2C slave functionality
  TinyWire.begin(adr);
  // register a handler function in case of a request from a master
  TinyWire.onRequest(sendToMaster);
  TinyWire.onReceive(getData);
  delay(200);
}

void loop(void) {
  delay(1000);
}

void sendToMaster(){
  TinyWire.send(digitalRead(led_pin));  
}

void getData(){
  while(TinyWire.available()>0){
    if(TinyWire.read()=='t'){
      digitalWrite(led_pin, !digitalRead(led_pin));
    }
  }
}
