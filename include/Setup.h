// Setup.h
#ifndef SETUP_H
#define SETUP_H
#define stepper_motors_velocity 800
#define stepper_motors_acceleration 600

#include <AccelStepper.h>
#include <Arduino.h>
#include <Bumper.h>
#include <ColorSensor.h>
#include <InfraredSensor.h>
#include <LED.h>
#include <MotorDC.h>
#include <Robot.h>
#include <Servo.h>
#include <SoftwareSerial.h>
#include <UltrasonicSensor.h>

// Define os objetos como globais
extern AccelStepper motor1;
extern AccelStepper motor2;
extern AccelStepper motor3;
extern AccelStepper motor4;
extern UltrasonicSensor usSensorFront;
extern UltrasonicSensor usSensorRight;
extern UltrasonicSensor usSensorLeft;
extern UltrasonicSensor usSensorTable;
extern InfraredSensor irSensorTableHeight1;
extern InfraredSensor irSensorTableHeight2;
extern InfraredSensor irSensorTableHeight3;
extern InfraredSensor irSensorTableHeight4;
extern ColorSensor clawSensor;
extern ColorSensor LeftFloorSensor;
extern ColorSensor RightFloorSensor;
extern Servo clawServo;
extern LED rgbLED;
extern SoftwareSerial raspy;
extern Bumper clawBumper;
extern MotorDC clawMotor;
extern Robot Tortuga;

// Função de configuração
void start();

#endif 
