#include <Arduino.h>
#include "AccelStepper.h"
#include "Tempo.h"
 
AccelStepper motor1(AccelStepper::DRIVER, 50, 52);
 
void setup() {
  motor1.setMaxSpeed(300);
}
 
void loop() {
    motor1.run();
    delay(3000);
}

/*

#include <Arduino.h>
#include "A4988.h"
 
int Step = 50; //GPIO14---D5 of Nodemcu--Step of stepper motor driver
int Dire  = 52; //GPIO2---D4 of Nodemcu--Direction of stepper motor driver
int Sleep = 12; //GPIO12---D6 of Nodemcu-Control Sleep Mode on A4988
int MS1 = 13; //GPIO13---D7 of Nodemcu--MS1 for A4988
int MS2 = 16; //GPIO16---D0 of Nodemcu--MS2 for A4988
int MS3 = 15; //GPIO15---D8 of Nodemcu--MS3 for A4988
 
//Motor Specs
const int spr = 200; //Steps per revolution
int RPM = 100; //Motor Speed in revolutions per minute
int Microsteps = 1; //Stepsize (1 for full steps, 2 for half steps, 4 for quarter steps, etc)
 
//Providing parameters for motor control
A4988 stepper(spr, Dire, Step, MS1, MS2, MS3);
 
void setup() {
  Serial.begin(9600);
  pinMode(Step, OUTPUT); //Step pin as output
  pinMode(Dire,  OUTPUT); //Direcction pin as output
  pinMode(Sleep,  OUTPUT); //Set Sleep OUTPUT Control button as output
  digitalWrite(Step, LOW); // Currently no stepper motor movement
  digitalWrite(Dire, LOW);
  
  // Set target motor RPM to and microstepping setting
  stepper.begin(RPM, Microsteps);
}
 
void loop() {
    digitalWrite(Sleep, HIGH); //A logic high allows normal operation of the A4988 by removing from sleep
     stepper.rotate(360);
}

*/