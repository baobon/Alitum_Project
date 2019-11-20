#include <AccelStepper.h>
int PUL=8; //define Pulse pin
int DIR=9; //define Direction pin
int tien =10;
int lui  =11;
#define HALFSTEP 8
#define motorPin1  2     // IN1 on the ULN2003 driver 1
#define motorPin2  3     // IN2 on the ULN2003 driver 1
#define motorPin3  4     // IN3 on the ULN2003 driver 1
#define motorPin4  5  
AccelStepper stepper1(HALFSTEP, motorPin1, motorPin3, motorPin2, motorPin4);
int turnSteps = 2100; // number of steps for a 90 degree turn
int lineSteps = -6600; //number of steps to drive straight
int stepperSpeed = 1000; //speed of the stepper (steps per second)
int steps1 = 0; // keep track of the step count for motor 1
boolean turn1 = false;

void uln2003(){
  Serial.println("Run uln2003");
  digitalWrite(12,HIGH);   
  digitalWrite(13,HIGH);
  if (steps1 == 0) {
    int target = 0;
    if (turn1 == true) {
      target = turnSteps;
    }
    else {
      target = lineSteps;
    }
    stepper1.move(target);
    stepper1.setSpeed(stepperSpeed);
    turn1 = !turn1;
  }
  steps1 = stepper1.distanceToGo();
  stepper1.runSpeedToPosition();
}

void setup() {
  pinMode (PUL, OUTPUT);
  pinMode (DIR, OUTPUT);
  pinMode(10,INPUT);
  pinMode(11,INPUT);
  pinMode(12,OUTPUT);
  pinMode(13,OUTPUT);
  digitalWrite(12,LOW);
  digitalWrite(13,LOW);
  stepper1.setMaxSpeed(2000.0);
  stepper1.move(1);  // I found this necessary
  stepper1.setSpeed(stepperSpeed);
  Serial.begin(9600);
}

void loop() {

   Serial.print(digitalRead(tien));
   Serial.print("        ");
   Serial.println(digitalRead(lui));
  
  if(digitalRead(tien)==0)
  { 
    Serial.println("Run step tien");
    digitalWrite(12,HIGH);   
    digitalWrite(13,LOW);
    for(int i=0;i<100;i++){
    digitalWrite(DIR,LOW);
    digitalWrite(PUL,HIGH);
    delayMicroseconds(1500);
    digitalWrite(PUL,LOW);
    delayMicroseconds(1);
    }
  }
  else if(digitalRead(tien)==1)
  { 
    if(digitalRead(lui)==0)
    {
    Serial.println("Run step lui");
    digitalWrite(12,LOW);   
    digitalWrite(13,HIGH);
    for(int i=0;i<100;i++){
    digitalWrite(DIR,HIGH);
    digitalWrite(PUL,HIGH);
    delayMicroseconds(1500);
    digitalWrite(PUL,LOW);
    delayMicroseconds(1);
    }
    }
    else if(digitalRead(lui)==1)
    {
      uln2003();
    }
  }
}
