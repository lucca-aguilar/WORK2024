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
    UltrasonicSensor usSensorTable;
    InfraredSensor irSensorTableHeight1;
    InfraredSensor irSensorTableHeight2;
    InfraredSensor irSensorTableHeight3;
    InfraredSensor irSensorTableHeight4;
    Servo clawServo;
    ColorSensor clawSensor;
    ColorSensor floorSensor;
    LED rgbLED;
    SoftwareSerial raspy;
    Bumper clawBumper;
    MotorDC clawMotor;

public:
    // construtor da classe robot
    Robot(AccelStepper& motor1, AccelStepper& motor2, AccelStepper& motor3, AccelStepper& motor4, UltrasonicSensor& usSensorFront, UltrasonicSensor& usSensorRight, UltrasonicSensor& usSensorLeft, UltrasonicSensor& usSensorTable, InfraredSensor& irSensorTableHeight1, InfraredSensor& irSensorTableHeight2, InfraredSensor& irSensorTableHeight3, InfraredSensor& irSensorTableHeight4, Servo& clawServo, ColorSensor& clawSensor, ColorSensor& floorSensor, LED& rgbLED, SoftwareSerial& raspy, Bumper& clawBumper, MotorDC& clawMotor)
        : motor1(motor1), motor2(motor2), motor3(motor3), motor4(motor4), usSensorFront(usSensorFront), usSensorRight(usSensorRight), usSensorLeft(usSensorLeft), usSensorTable(usSensorTable), irSensorTableHeight1(irSensorTableHeight1), irSensorTableHeight2(irSensorTableHeight2), irSensorTableHeight3(irSensorTableHeight3), irSensorTableHeight4(irSensorTableHeight4), clawServo(clawServo), clawSensor(clawSensor), floorSensor(floorSensor), rgbLED(rgbLED), raspy(raspy), clawBumper(clawBumper), clawMotor(clawMotor) {}

    // metodos de configuracao
    void servoConfiguration();
    void serialConfiguration();

    // metodos mais gerais???
    void getCubeFront(int table_height);
    void getCubeBack(int table_height);
    int cubePresence();
    void motorsConfiguration(int velocity, int acceleration);

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
    void defaultClawPosition();
    void placeCube();

    // metodos dos sensores infravermelhos da torre
    int checkTableHeightFront();
    int checkTableHeightBack();
    int checkForCubeFront(int tableHeight);
    int checkForCubeBack(int tableHeight);

    // metodos envolvendo sensor de cor
    char checkCubeColor();
    char checkFloorColor();

    // metodos envolvendo visao
    int checkVirtualWall();
    int virtualWallDistance();
    int readTag();
    char checkConteinerColor(); 
};

#endif