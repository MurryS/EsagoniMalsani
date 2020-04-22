#include <OneWire.h>

// OneWire DS18S20, DS18B20, DS1822 Temperature Example

OneWire ds(2); // on pin 2 (a 4.7K resistor is necessary)
byte addr[8];
byte type_s;
byte data[12];
float celsius;

void setup(void) {
 Serial.begin(9600);
 ds.search(addr); //cerco indirizzo DS1822 //ROM = 22 5D BE 63 0 0 0 4
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

 
 Serial.print(" Temperature = ");
 Serial.print(celsius);
 Serial.println(" Celsius, ");
}

void startConv(){
  ds.reset();
  ds.select(addr);
  ds.write(0x44, 1); // start conversion, with parasite power on at the end
}
