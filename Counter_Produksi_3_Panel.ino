#include "DMD3.h"
#include "EEPROM.h"
#include "bmz15x32.h"
#include "bmz10x16.h"
#include "bmzSegment16.h"
#include "bmzSegment32.h"
#include "bmz6x16.h"
#include "bmz5x7.h"
#include "bmzLogo.h"


DMD3 display (2,3);

byte debounce1 = 100;
byte debounce2 = 100;
byte debounce3 = 100;
char dmdBuff1[10];
char dmdBuff2[10];
char dmdBuff3[10];

unsigned long int target = 0;
unsigned long int actual = 0;
unsigned long int balance = 0;

void scan()
{
    display.refresh();
}

 
void setup() {
    Timer1.initialize(1350);
    Timer1.attachInterrupt(scan);
    Timer1.pwm(9,100);

    pinMode(A0, INPUT_PULLUP);
    pinMode(A1, INPUT_PULLUP);
    pinMode(A2, INPUT_PULLUP);

    Serial.begin(9600);
}

void loop() {

    int val1 = EEPROM.read(102);
    int val2 = EEPROM.read(103);
    int val3 = EEPROM.read(104);
     balance=val1-val2;
    sprintf(dmdBuff1, "%.4d", val1);
    sprintf(dmdBuff2, "%.4d", val2);
    sprintf(dmdBuff3, "%.4d", balance);
 
    display.setFont(bmz6x16);
    display.drawText(36, 0, dmdBuff1);
    display.drawText(36, 16, dmdBuff2);
    display.drawText(36, 32, dmdBuff3);

     display.setFont(bmz5x7);
    display.drawText(3, 4, "PLAN");
    display.drawText(3, 20, "REAL");
    display.drawText(3, 36, "DIFF");
    //display.drawText(0, 8, "LINE A");
    //display.drawText(0, 24, "LINE A");
    //display.drawText(0, 40, "LINE A");
    
    if(digitalRead(A0)==LOW){
      delay(200);
      actual++; 
      EEPROM.write(103,actual);
    }

   
    

    if(target > 9999){
      target = 0000;
    }

    if(target < 0000){
      target = 0000;
    }

     if(actual > 9999){
      actual = 0000;
    }

    if(actual < 0000){
      actual = 0000;
    }
    
    if(digitalRead(A1)==LOW){
      target++;
      EEPROM.write(102,target);
    }

    if(digitalRead(A2)==LOW){
      target--;
      EEPROM.write(102,target);
    }
}
