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
#define true 0
#define false 1

// declaracao de componentes

// motores de passo
AccelStepper motor1(AccelStepper::DRIVER, 52, 50);
AccelStepper motor2(AccelStepper::DRIVER, 51, 53);
AccelStepper motor3(AccelStepper::DRIVER, 47, 49);
AccelStepper motor4(AccelStepper::DRIVER, 45, 43);

// sensores ultrassônicos
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
LED blueLED(0);
LED redLED(0);

// raspberry
SoftwareSerial raspy(0, 0);

// bumper
Bumper clawBumper(22);

// motor dc
MotorDC clawMotor(21, 20, 9, 0, 0);

// robot
Robot Tortuga(motor1, motor2, motor3, motor4, usSensorFront, usSensorRight, usSensorLeft, irSensorLFR, irSensorLFC, irSensorLFL, irSensorTableHeight1, irSensorTableHeight2, irSensorTableHeight3, irSensorTableHeight4, clawServo, clawSensor, blueLED, redLED, raspy, clawBumper, clawMotor);

void setup() {
    // condiguracao
    Tortuga.servoConfiguration();
    Tortuga.motorsConfiguration();
    Tortuga.serialConfiguration();
}

void loop() {
    while (1) {
      Tortuga.moveForward(150);
      int front_distance = usSensorFront.getDistance();
      Serial.println("Front distance:");
      Serial.println(front_distance);
      if (front_distance <= 10) {
        Tortuga.stop();
        break;
      }
    }
    int table_height = Tortuga.checkTableHeight();
    Tortuga.checkForCube(table_height);
  }

// comentado - testes
/*
// testes com infravermelho
   int distanceIR1 = irSensorTableHeight1.measureDistance();
   int distanceIR2 = irSensorTableHeight2.measureDistance();
   int distanceIR3 = irSensorTableHeight3.measureDistance();
   int distanceIR4 = irSensorTableHeight4.measureDistance();

   int distanceLFL = irSensorLFL.measureDistance();
   int distanceLFC = irSensorLFC.measureDistance();
   int distanceLFR = irSensorLFR.measureDistance();

   Serial.print("Ir1 =");
   Serial.println(distanceIR1);
   Serial.print("Ir2 =");
   Serial.println(distanceIR2);
   Serial.print("Ir3 =");
   Serial.println(distanceIR3);
   Serial.print("Ir4 =");
   Serial.println(distanceIR4);
   Serial.println(".");

   Serial.print("IrLFL =");
   Serial.println(distanceLFL);
   Serial.print("IrLFC =");
   Serial.println(distanceLFC);
   Serial.print("IrLFR =");
   Serial.println(distanceLFR);
   Serial.println(".");

// testes com ultrassonicos
   int distanceLeft = usSensorLeft.getDistance();
   int distanceFront = usSensorFront.getDistance();
   int distanceRight = usSensorRight.getDistance();

   Serial.print("USL =");
   Serial.println(distanceLeft);
   Serial.print("USF =");
   Serial.println(distanceFront);
   Serial.print("USR =");
   Serial.println(distanceRight);

// teste servo
  clawServo.write(80);
  delay(2000);
  clawServo.write(105);
  delay(2000);

// teste com motores de passo (movimentacao)
  moveForward(100);
  moveBackward(100);
  moveRight(100);
  moveLeft(100);

  // teste movimentação basica
 while (1) {
      Tortuga.moveForward(150);
      int front_distance = usSensorFront.getDistance();
      Serial.println("Front distance:");
      Serial.println(front_distance);
      if (front_distance <= 10) {
        Tortuga.stop();
        break;
      }
    }
    int table_height = Tortuga.checkTableHeight();
    Tortuga.checkForCube(table_height);

  // teste sensor de cor
    char* color = Tortuga.checkCubeColor();
    Serial.println(color);
    Serial.println("\n");
*/
// lalalalala