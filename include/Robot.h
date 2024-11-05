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
    MotorDC clawMotor;

public:
    // construtor da classe robot
    Robot(AccelStepper& motor1, AccelStepper& motor2, AccelStepper& motor3, AccelStepper& motor4, UltrasonicSensor& usSensorFront, UltrasonicSensor& usSensorRight, UltrasonicSensor& usSensorLeft, InfraredSensor& irSensorLFL, InfraredSensor& irSensorLFC, InfraredSensor& irSensorLFR, InfraredSensor& irSensorTableHeight1, InfraredSensor& irSensorTableHeight2, InfraredSensor& irSensorTableHeight3, InfraredSensor& irSensorTableHeight4, Servo& clawServo, ColorSensor& clawSensor, LED& blueLED, LED& redLED, SoftwareSerial& raspy, Bumper& clawBumper, MotorDC& clawMotor);

    // metodos de configuracao
    void servoConfiguration();
    void serialConfiguration();

    // metodos mais gerais???
    void getCube(int table_height);
    int cubePresence();
    void motorsConfiguration();

    // metodos de movimentacao
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
    void moveClawUp(int dc_dislocation);
    void moveClawDown(int dc_dislocation);

    // metodos dos sensores infravermelhos da torre
    int checkTableHeight();
    void checkForCube(int tableHeight);

    // metodos dos sensores infravermelhos segue linha
    void followLine(int activator);

    // metodos envolvendo sensor de cor
    char* checkCubeColor();

    // metodos envolvendo visao
    int checkVirtualWall();
    int virtualWallDistance();
    int readTag();
    int conteinerColor(); 

};

#endif