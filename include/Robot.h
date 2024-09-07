#include "AccelStepper.h"
#include "Arduino.h"
#include "Bumper.h"
#include "ColorSensor.h"
#include "InfraredSensor.h"
#include "LED.h"
#include "Servo.h"
#include "Tempo.h"
#include "UltrasonicSensor.h"
#include "Vision.h"

#ifndef ROBOT_H
#define ROBOT_H

class Robot {
public:
    AccelStepper R1, R2, L1, L2;
    Bumper button;
    ColorSensor clawSensor, frontSensor;
    InfraredSensor IR1, IR2, IR3, IR4;
    LED red, blue;
    Servo claw;
    UltrasonicSensor front, right, left;
    
private:

};

#endif