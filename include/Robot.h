#ifndef ROBOT_H
#define ROBOT_H

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

class Robot{
private:
    AccelStepper motor1;
    AccelStepper motor2;
    AccelStepper motor3;
    AccelStepper motor4;
    UltrasonicSensor usSensorFront;
    UltrasonicSensor usSensorRight;
    UltrasonicSensor usSensorLeft;
    InfraredSensor irSensorLFL;
    InfraredSensor irSensorLFC;
    InfraredSensor irSensorLFR;
    InfraredSensor irSensorTableHeight1;
    InfraredSensor irSensorTableHeight2;
    InfraredSensor irSensorTableHeight3;
    InfraredSensor irSensorTableHeight4;
    Servo clawServo;
    ColorSensor clawSensor;
    LED blueLED;
    LED redLED;
    SoftwareSerial raspy;
    Bumper clawBumper;

public:
    // construtor da classe robot
    Robot(AccelStepper& motor1, AccelStepper& motor2, AccelStepper& motor3, AccelStepper& motor4, UltrasonicSensor& usSensorFront, UltrasonicSensor& usSensorRight, UltrasonicSensor& usSensorLeft, InfraredSensor& irSensorLFR, InfraredSensor& irSensorLFC, InfraredSensor& irSensorLFL, InfraredSensor& irSensorTableHeight1, InfraredSensor& irSensorTableHeight2, InfraredSensor& irSensorTableHeight3, InfraredSensor& irSensorTableHeight4, Servo& clawServo, ColorSensor& clawSensor, LED& blueLED, LED& redLED, SoftwareSerial& raspy, Bumper& clawBumper);

    // metodos gerais


    // metodos de movimentacao
    void motorsConfiguration();
    void moveForward(int steps);
    void moveBackward(int steps);
    void moveLeft(int steps);
    void moveRight(int steps);
    void rotateClockwise(int steps);
    void rotateAntiClockwise(int steps);
    void stop();

    // metodos da garra
    void openClaw();
    void closeClaw();
    void moveClaw(int clawHeight);

    // metodos dos sensores infravermelhos da torre
    int checkTableHeight();
    int checkForCube(int tableHeight);

    // metodos dos sensores infravermelhos segue linha
    void followLine();
    void alignInLine();

};

#endif