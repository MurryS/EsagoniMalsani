//========================================================
// Light module
// Author:      Muraglia Alessandro
// Data:        29/04/2020
// IIC adress:  0x04
// Functions:
//    - Led on/off if required
//    - Microphone on interrupt
// 
// Pinout:
//    - mos on pin6 dip-8 (D1, PWM)
//    - microphone on pin2 dip-8 (D3, PCINT3)
//
//========================================================


#include <TinyWire.h>  //iic for attiny

#define adr 0x04
#define LED 1
#define Mic 3

byte data[8]; //dati che leggerò (data[0] = config; data[1] = led pwm value)
byte tgt; // valore a cui LED PWM deve convergere
byte actual;  //valore PWM LED
boolean state = HIGH; //set to on, False = led off
long last = 0;


//========================================================
//setup
//========================================================
void setup() {
  pinMode(LED, OUTPUT);
  pinMode(Mic, INPUT_PULLUP);
  // config TinyWire library for I2C slave functionality
  TinyWire.begin(adr);
  // register a handler function in case of a request from a master
  TinyWire.onRequest(sendToMaster);
  TinyWire.onReceive(getData);
  delay(200);
  last = millis();
}

//========================================================

//========================================================
void loop(void) {
  //lettura segnale microfono
  if(digitalRead(Mic)){
    state = !state;
    if(state == 1){
      tgt = 255;
    }else{tgt = 0;} 
  }
  //aggiornamento PWM
  if (millis()-last > 5){//change pwm
    if(actual < tgt){actual++;}
    if(actual > tgt){actual--;}
    analogWrite(LED, actual);
  }
  
}

//========================================================
// IIC methods
//========================================================
void sendToMaster(){
  TinyWire.send(data[0]); //invio le mie impostazioni
  TinyWire.send(tgt);     //invio il target per PWM LED
}

void getData(){
  while(TinyWire.available()>0){
    int i = 0;
    data[i] = TinyWire.read();
    i++;
  }
  //cambio luce
  tgt = data[1];
}
