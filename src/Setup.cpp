#include <AccelStepper.h>
#include <Arduino.h>
#include <Bumper.h>
#include <ColorSensor.h>
#include <InfraredSensor.h>
#include <LED.h>
#include <MotorDC.h>
#include <Robot.h>
#include <Servo.h>
#include <Setup.h>
#include <SoftwareSerial.h>
#include <UltrasonicSensor.h>
#define stepper_motors_velocity 800
#define stepper_motors_acceleration 600
#define true 0
#define false 1

 // declaracao dos componentes 
    AccelStepper motor1(AccelStepper::DRIVER, 52, 50);
    AccelStepper motor2(AccelStepper::DRIVER, 51, 53);
    AccelStepper motor3(AccelStepper::DRIVER, 47, 49);
    AccelStepper motor4(AccelStepper::DRIVER, 45, 43);

    // sensores ultrassônicos
    //UltrasonicSensor usSensorFront(39, 41);
    UltrasonicSensor usSensorFront(39, 41);
    UltrasonicSensor usSensorRight(31, 33);
    UltrasonicSensor usSensorLeft(37, 35);

    // sensores infravermelho
    InfraredSensor irSensorLFL(11, 0);  //lineFollowerLeft if1
    InfraredSensor irSensorLFC(6, 0);  //lineFollowerCenter if6
    InfraredSensor irSensorLFR(5, 0);  //lineFollowerRight if7

    InfraredSensor irSensorTableHeight1(12, 0); //Top sensor if2
    InfraredSensor irSensorTableHeight2(10, 0); // if3
    InfraredSensor irSensorTableHeight3(9, 0); // if4
    InfraredSensor irSensorTableHeight4(7, 0); //Bottom sensor if5

    // sensor de cor da garra
    ColorSensor clawSensor(17, 16, 14, 15, 18);

    // servo motor da garra
    Servo clawServo;

    // leds
    LED rgbLED(24, 22);

    // raspberry
    SoftwareSerial raspy(0, 0);

    // bumper
    Bumper clawBumper(22);

    // motor dc
    MotorDC clawMotor(21, 20, 5, 0, 0);

    // robot
    Robot Tortuga(motor1, motor2, motor3, motor4, usSensorFront, usSensorRight, usSensorLeft, irSensorLFR, irSensorLFC, irSensorLFL, irSensorTableHeight1, irSensorTableHeight2, irSensorTableHeight3, irSensorTableHeight4, clawServo, clawSensor, rgbLED, raspy, clawBumper, clawMotor);

void start() {
    // configuracoes
    Serial.begin(9600);
    Tortuga.servoConfiguration();
    Tortuga.motorsConfiguration(stepper_motors_velocity, stepper_motors_acceleration);
    Tortuga.serialConfiguration();
};




