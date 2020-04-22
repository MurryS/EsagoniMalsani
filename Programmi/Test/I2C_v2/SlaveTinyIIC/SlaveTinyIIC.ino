#include <TinyWire.h>
#include <OneWire.h>

#define adr 0x04

OneWire ds(3); // on pin 3 (a 4.7K resistor is necessary)
byte addr[8] = {0x22, 0x5D, 0xBE, 0x63, 0x0, 0x0, 0x0, 0x4};
byte data[12];
float celsius;

void setup() {
  // config TinyWire library for I2C slave functionality
  TinyWire.begin(adr);
  // register a handler function in case of a request from a master
  TinyWire.onRequest(sendToMaster);
  delay(200);
}

void loop(void) {
startConv();
 delay(1000); // maybe 750ms is enough, maybe not
  
 ds.reset();
 ds.select(addr); 
 ds.write(0xBE); // Read Scratchpad

 for (int i = 0; i < 9; i++) { // we need 9 bytes
    data[i] = ds.read();
 }
 int16_t raw = (data[1] << 8) | data[0];
 byte cfg = (data[4] & 0x60);
 
 if (cfg == 0x00) raw = raw & ~7; // 9 bit resolution, 93.75 ms
 else if (cfg == 0x20) raw = raw & ~3; // 10 bit res, 187.5 ms
 else if (cfg == 0x40) raw = raw & ~1; // 11 bit res, 375 ms

 celsius = (float)raw / 16.0;
}

void startConv(){
  ds.reset();
  ds.select(addr);
  ds.write(0x44, 1); // start conversion, with parasite power on at the end
}

void sendToMaster() {
  for(int i = 0; i < 8; i++){
    TinyWire.send(data[i]);  
  }
}
