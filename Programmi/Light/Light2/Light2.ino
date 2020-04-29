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



#define adr 0x04
#define LED 5 //!!!!!!!!!!!!!!!!!!!!da mettere sul 2
#define Mic 3

#define ramptime 10 //ms

byte data[8]; //dati che leggerò (data[0] = config; data[1] = led pwm value)
byte tgt = 255; // valore a cui LED PWM deve convergere
byte actual = 0;  //valore PWM LED
boolean state = HIGH; //set to on, False = led off
long last = 0;
long lastchange = 0;


//========================================================
//setup
//========================================================
void setup() {
  pinMode(LED, OUTPUT);
  pinMode(Mic, INPUT_PULLUP);
  delay(200);
  last = millis();
  lastchange = millis();
}

//========================================================

//========================================================
void loop(void) {
  //lettura segnale microfono
  if(digitalRead(Mic)==0&&(millis() - lastchange > 200)){
    state = !state;
    lastchange = millis();
    if(state == 1){
      tgt = 255;
    }else{tgt = 0;} 
  }
  //aggiornamento PWM
  if (millis()-last > ramptime){//change pwm
    if(actual < tgt){actual = actual + 1;}
    if(actual > tgt){actual = actual - 1;}
    analogWrite(LED, actual);
    last = millis();
  }
  
}
