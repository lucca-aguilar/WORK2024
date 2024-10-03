#include "AccelStepper.h"
#include "Arduino.h"
#include "Bumper.h"
#include "ColorSensor.h"
#include "InfraredSensor.h"
#include "LED.h"
#include "MotorDC.h"
#include "Servo.h"
#include "Tempo.h"
#include "UltrasonicSensor.h"
#include "Vision.h"
#include "Robot.h"

// Construtor da classe Robot
Robot::Robot(AccelStepper motor1, AccelStepper motor2, AccelStepper motor3, AccelStepper motor4, UltrasonicSensor usSensorFront, UltrasonicSensor
usSensorRight, UltrasonicSensor usSensorLeft, InfraredSensor irSensorLFR, InfraredSensor irSensorLFC, InfraredSensor irSensorLFL) : motor1(motor1, motor2(motor2)){}

void Robot::moveForward(int steps) {
    motor2.move(-steps);
    motor3.move(-steps);

    while (motor1.distanceToGo() != 0 || motor2.distanceToGo() != 0 || motor3.distanceToGo() != 0 || motor4.distanceToGo() != 0) {
    motor2.run();
    motor3.run();
  }
};

void Robot::moveBackward(int steps) {
    motor2.move(steps);
    motor3.move(steps);

    while (motor1.distanceToGo() != 0 || motor2.distanceToGo() != 0 || motor3.distanceToGo() != 0 || motor4.distanceToGo() != 0) {
        motor2.run();
        motor3.run();
    }
};

void Robot::moveLeft(int steps) {
    motor1.move(steps);
    motor4.move(steps);

    while (motor1.distanceToGo() != 0 || motor2.distanceToGo() != 0 || motor3.distanceToGo() != 0 || motor4.distanceToGo() != 0) {
        motor1.run();
        motor4.run();
    }
};

void Robot::moveRight(int steps) {
    motor1.move(-steps);
    motor4.move(-steps);

    while (motor1.distanceToGo() != 0 || motor2.distanceToGo() != 0 || motor3.distanceToGo() != 0 || motor4.distanceToGo() != 0) {
        motor1.run();
        motor4.run();
    }
};

void Robot::rotateClockwise(int steps) {
  motor1.move(steps);
  motor2.move(steps);
  motor3.move(-steps);
  motor4.move(-steps);

  while (motor1.distanceToGo() != 0 || motor2.distanceToGo() != 0 || motor3.distanceToGo() != 0 || motor4.distanceToGo() != 0) {
    motor1.run();
    motor2.run();
    motor3.run();
    motor4.run();
  }
};

void Robot::rotateAntiClockwise(int steps) {
  motor1.move(-steps);
  motor2.move(-steps);
  motor3.move(steps);
  motor4.move(steps);

  while (motor1.distanceToGo() != 0 || motor2.distanceToGo() != 0 || motor3.distanceToGo() != 0 || motor4.distanceToGo() != 0) {
    motor1.run();
    motor2.run();
    motor3.run();
    motor4.run();
  }
};

void runForward(){

};

void runBackward(){

};

void runLeft(){

};

void runRight(){

};

void Robot::motorsConfiguration(){
    motor1.setMaxSpeed(100);  // Velocidade máxima em passos/segundo
    motor1.setAcceleration(200);  // Aceleração em passos/segundo^2
    
    motor2.setMaxSpeed(100);
    motor2.setAcceleration(200);

    motor3.setMaxSpeed(115);
    motor3.setAcceleration(200);

    motor4.setMaxSpeed(100);
    motor4.setAcceleration(200);
};

long Robot::usReadFront(){
    usSensorFront.getDistance();
};

long Robot::usReadRight(){
    usSensorRight.getDistance();
};

long Robot::usReadLeft(){
    usSensorLeft.getDistance();
};

int irReadLFR(){

};

int irReadLFC(){

};

int irReadLCL(){
    
};

