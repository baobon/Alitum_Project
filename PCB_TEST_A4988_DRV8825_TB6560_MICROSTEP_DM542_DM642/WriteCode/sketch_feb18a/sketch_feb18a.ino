#include <AccelStepper.h>
int PUL=8; //define Pulse pin
int DIR=9; //define Direction pin

void setup() {
    pinMode (PUL, OUTPUT);
  pinMode (DIR, OUTPUT);

}

void loop() {
    for(int i=0;i<1000;i++){
    digitalWrite(DIR,HIGH);
    digitalWrite(PUL,HIGH);
    delayMicroseconds(1500);
    digitalWrite(PUL,LOW);
    delayMicroseconds(1);
    }
    for(int i=0;i<1000;i++){
    digitalWrite(DIR,LOW);
    digitalWrite(PUL,HIGH);
    delayMicroseconds(1500);
    digitalWrite(PUL,LOW);
    delayMicroseconds(1);
    }

    
}
