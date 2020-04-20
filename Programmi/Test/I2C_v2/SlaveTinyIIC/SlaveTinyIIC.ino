#include <TinyWire.h>
#include <OneWire.h>

#define adr 0x04

OneWire ds(2); // on pin 2 (a 4.7K resistor is necessary)
byte addr[8];
float celsius;

void setup() {
  // config TinyWire library for I2C slave functionality
  TinyWire.begin(adr);
  // register a handler function in case of a request from a master
  TinyWire.onRequest(Request);
  delay(200);
  ds.search(addr); //cerco indirizzo DS1822 //ROM = 22 5D BE 63 0 0 0 4
}

void loop(void) {
 startConv();
 delay(1000); // maybe 750ms is enough, maybe not
 celsius = readTemp();
 delay(500);
}


void Request() {
  TinyWire.send(celsius);
}

void startConv(){
  ds.reset();
  ds.select(addr);
  ds.write(0x44, 1); // start conversion, with parasite power on at the end
}

float readTemp(){
  byte data[12];
  ds.reset();
  ds.select(addr); 
  ds.write(0xBE); // Read Scratchpad  
  for (int i = 0; i < 9; i++) { // we need 9 bytes
    data[i] = ds.read();
  }
  int16_t raw = (data[1] << 8) | data[0];
  return (float)raw / 16.0;
}
