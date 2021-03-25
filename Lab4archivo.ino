
/*
  Hardware Required:
  * LaunchPad with an LED
*/

// most launchpads have a red LED

#include <stdint.h>

//luces del semáforo (luz rbg)
#define BLED PF_1
#define LEDB PF_2
#define RLED PF_3

//pines de las luces led
#define BLED0 PD_0  //LEDS AZULES - P1
#define BLED1 PD_1
#define BLED2 PD_2
#define BLED3 PD_3
#define BLED4 PE_1
#define BLED5 PE_2
#define BLED6 PE_3
#define BLED7 PA_7
#define RLED0 PB_3 //LEDS ROJOS - P2
#define RLED1 PC_4
#define RLED2 PC_5
#define RLED3 PC_6
#define RLED4 PC_7
#define RLED5 PD_6
#define RLED6 PD_7
#define RLED7 PA_2

//funciones y variables 
uint8_t cont1, cont2, BEGIN; 
void semaforo(void);
void myreset(void);
void show(void);
void PUSH1f(void);
void PUSH2f(void);
byte ports(uint8_t);
const int  PUSHB1 = PUSH1;
const int  PUSHB2 = PUSH2;
//const int  PUSHB3 = PUSH3;

byte LEDBbytes = 0b00000000; 
byte LEDRbytes = 0b00000000;

void myreset(){
  cont1 = cont2 = 0;
  BEGIN = 0; 
  LEDRbytes = 0b00000000;
  LEDBbytes = 0b00000000;
}

//setup 
void setup() {
  // put your setup code here, to run once:

  //SETUP FOR THE RGB LED
  pinMode(BLED, OUTPUT);  
  pinMode(RLED, OUTPUT);  
  pinMode(LEDB, OUTPUT);

/*
 * SETUP FOR THE BLUE (P1) AND RED (P2) LEDS AS OUTPUTS
*/
  pinMode(BLED0, OUTPUT);
  pinMode(BLED1, OUTPUT);
  pinMode(BLED2, OUTPUT);
  pinMode(BLED3, OUTPUT);
  pinMode(BLED4, OUTPUT);
  pinMode(BLED5, OUTPUT);
  pinMode(BLED6, OUTPUT);
  pinMode(BLED7, OUTPUT);
  pinMode(RLED0, OUTPUT);
  pinMode(RLED1, OUTPUT);
  pinMode(RLED2, OUTPUT);
  pinMode(RLED3, OUTPUT);
  pinMode(RLED4, OUTPUT);
  pinMode(RLED5, OUTPUT);
  pinMode(RLED6, OUTPUT);
  pinMode(RLED7, OUTPUT);  

  // PUSHBUTTONS
  pinMode(PUSHB1, INPUT_PULLUP);
  pinMode(PUSHB2, INPUT_PULLUP);
 // pinMode(PUSHB3, INPUT_PULLUP);
  
  attachInterrupt(digitalPinToInterrupt(PUSHB1), PUSH1f, FALLING);
  attachInterrupt(digitalPinToInterrupt(PUSHB2), PUSH2f, FALLING);
 // attachInterrupt(digitalPinToInterrupt(PUSHB3), PUSH3f, FALLING);
  myreset();
}

void show() {
    digitalWrite(BLED0, bitRead(LEDBbytes,0));
    digitalWrite(BLED1, bitRead(LEDBbytes,1));
    digitalWrite(BLED2, bitRead(LEDBbytes,2));
    digitalWrite(BLED3, bitRead(LEDBbytes,3));
    digitalWrite(BLED4, bitRead(LEDBbytes,4));
    digitalWrite(BLED5, bitRead(LEDBbytes,5));
    digitalWrite(BLED6, bitRead(LEDBbytes,6));
    digitalWrite(BLED7, bitRead(LEDBbytes,7));

    digitalWrite(RLED0, bitRead(LEDRbytes,0));
    digitalWrite(RLED1, bitRead(LEDRbytes,1));
    digitalWrite(RLED2, bitRead(LEDRbytes,2));
    digitalWrite(RLED3, bitRead(LEDRbytes,3));
    digitalWrite(RLED4, bitRead(LEDRbytes,4));
    digitalWrite(RLED5, bitRead(LEDRbytes,5));
    digitalWrite(RLED6, bitRead(LEDRbytes,6));
    digitalWrite(RLED7, bitRead(LEDRbytes,7));
    return;
  }

byte ports(uint8_t x) {
  switch (x){
    case 1: return 0b00000001;
    break;
    case 2: return 0b00000010;
    break;
    case 3: return 0b00000100;
    break;
    case 4: return 0b00001000;
    break;
    case 5: return 0b00010000;
    break;
    case 6: return 0b00100000;
    break;
    case 7: return 0b0100000;
    break;
    case 8: return 0b1000000;
    break;
    case 9: 
    if(cont1 == 9){
      digitalWrite(BLED, HIGH);
      LEDBbytes = 0b11111111;
      show();
      delay(1000);
      }
    if(cont2 == 9){
      digitalWrite(RLED, HIGH);
      LEDRbytes = 0b11111111;
      show();
      delay(1000);
      }
    return 0b00000000 ;
    myreset();
    break;
      
  }
} 


void PUSH1f(){
    if (BEGIN == 1){
      cont1 = cont1++;
      LEDBbytes = ports(cont1);
      show();
    }
    return;
  }
  
void PUSH2f(){
    if (BEGIN == 1){
      cont2 = cont2++;
      LEDRbytes = ports(cont2);
      show();
    }
    return;
  }


//funcion de la secuencia del semáforo
void semaforo(void){
  digitalWrite(BLED, HIGH);
  delay(1000);
  digitalWrite(RLED, HIGH);
  delay(1000);
  digitalWrite(BLED, LOW);
  digitalWrite(RLED, HIGH);
  delay(1000);
  digitalWrite(RLED, LOW);
  BEGIN++;
  return;
}

void loop() {
  // put your main code here, to run repeatedly:

  if ((digitalRead(PUSHB1) == 0 || digitalRead(PUSHB2) == 0) && BEGIN == 0){
    semaforo();
    }

}
