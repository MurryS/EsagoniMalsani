//==================================================================================================================================================================
//  Author : Muraglia Alessandro
//  File   : Led_lampada_2
//  Data   : 05/07/16
//  Pinout :
//          - cap_sense on     : 2 - 4 - 6
//          - potentiometer on : A0 - A1 - A2
//          - leds on board on : D3 - D5
//          - push button on   : A5 - A6 - A7
//          - rgb on           : D9  D10 - D11
//  Version: 1.0.1
//==================================================================================================================================================================

#include <CapacitiveSensor.h>

CapacitiveSensor   cs_4_2 = CapacitiveSensor(4,2);        // 10M resistor between pins 4 & 2, pin 2 is sensor pin
CapacitiveSensor   cs_4_6 = CapacitiveSensor(4,6);        // 10M resistor between pins 4 & 6, pin 6 is sensor pin
CapacitiveSensor   cs_4_8 = CapacitiveSensor(4,8);        // 10M resistor between pins 4 & 8, pin 8 is sensor pin

#define red     9
#define green   10
#define blue    11


char abilitazione = 0;   //flag per indicare se si è in modifica o no
char range = 0;          //range per separare accensione da modifica
int rosso_wanted = 0;   //valore desiderato
int verde_wanted = 0;   //valore desiderato
int blu_wanted = 0;     //valore desiderato
int rosso = 0;          //PWM r
int verde = 0;          //PWM g
int blu = 0;            //PWM b
char max_value = 0;      //valore massimo dell'acquisizione da capsense
int total1 = 0;          //variabili per sensore
int total2 = 0;          //variabili per sensore
int total3 = 0;          //variabili per sensore

//==================================================================================================================================================================

void setup(){
   Serial.begin(9600);
   pinMode(red,OUTPUT);
   pinMode(green,OUTPUT);
   pinMode(blue,OUTPUT);
   pinMode(3,OUTPUT);    //led di test
   pinMode(5,OUTPUT);    //led di test
   range = 200;
   max_value = 1300;
}

//==================================================================================================================================================================

void loop(){
    digitalWrite(3,HIGH);
    lettura();
    if(abilitazione == 1){
        digitalWrite(5,HIGH);
        modifica();       
    }
    scrittura();  
    
//    long start = millis();
//    Serial.print(millis() - start);
//      Serial.print(rosso_wanted);
//      Serial.print("     ");
//      Serial.print(total1);
//      Serial.println("   ");

    //attesa per la rampa di avvicinamento che cambia ad ogni ciclo x->x_wanted
    delay(50);
    digitalWrite(5,LOW);    
}

//==================================================================================================================================================================

void lettura(void){
    // lettura          .capSense(sensibilità);
    total1 =  cs_4_2.capacitiveSensor(30);
    total2 =  cs_4_6.capacitiveSensor(30);
    total3 =  cs_4_8.capacitiveSensor(30);
    if((total1>range)||(total2>range)||(total3>range)){
        abilitazione = 1;   
    }
    else{
        abilitazione = 0;
    }
}

//==================================================================================================================================================================

void modifica(void){
    rosso_wanted = map (total1,0,255,0,max_value);
    verde_wanted = map (total2,0,255,0,max_value);
    blu_wanted = map (total3,0,255,0,max_value); 
}

//==================================================================================================================================================================

void scrittura(void){
    if(rosso<rosso_wanted){
        rosso++;
    }
    if(rosso>rosso_wanted){
        rosso = rosso -1;
    }
    if(verde<verde_wanted){
        verde++;
    }
    if(verde>verde_wanted){
        verde = verde -1;
    }
    if(blu<blu_wanted){
        blu++;
    }
    if(blu>blu_wanted){
        blu = blu -1;
    }
    //PWM
    analogWrite(red,rosso);
    analogWrite(green,verde);
    analogWrite(blue,blu);
}

//==================================================================================================================================================================
// END
//==================================================================================================================================================================
