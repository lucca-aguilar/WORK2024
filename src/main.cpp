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

// declaracao de componentes

// motores de passo
AccelStepper motor1(AccelStepper::DRIVER, 51, 53);
AccelStepper motor2(AccelStepper::DRIVER, 52, 50);
AccelStepper motor3(AccelStepper::DRIVER, 49, 47);
AccelStepper motor4(AccelStepper::DRIVER, 45, 43);

// sensores ultrassônicos
UltrasonicSensor usSensorFront(21, 20);
UltrasonicSensor usSensorRight(16, 17);
UltrasonicSensor usSensorLeft(37, 35);

// sensores infravermelho
InfraredSensor irSensorLFL(0, 0);  //lineFollowerLeft
InfraredSensor irSensorLFC(7, 0);  //lineFollowerCenter
InfraredSensor irSensorLFR(8, 0);  //lineFollowerRight

InfraredSensor irSensorTableHeight1(1, 0); //Top sensor
InfraredSensor irSensorTableHeight2(6, 0);
InfraredSensor irSensorTableHeight3(5, 0);
InfraredSensor irSensorTableHeight4(11, 0); //Bottom sensor

// sensor de cor da garra
ColorSensor clawSensor(30, 28, 24, 26, 22);

// servo motor da garra
Servo clawServo;

// leds
LED blueLED(0);
LED redLED(0);

// raspberry
SoftwareSerial raspy(0, 0);

// bumper
Bumper clawBumper(0);

// motor dc
MotorDC clawMotor(50, 52, 3, 0, 0);

// robot
Robot Tortuga(motor1, motor2, motor3, motor4, usSensorFront, usSensorRight, usSensorLeft, irSensorLFR, irSensorLFC, irSensorLFL, irSensorTableHeight1, irSensorTableHeight2, irSensorTableHeight3, irSensorTableHeight4, clawServo, clawSensor, blueLED, redLED, raspy, clawBumper, clawMotor);

void setup() {

    // configuracao de porta serial
    Serial.begin(9600);

    // configuracao comunicacao raspy (rx-tx)
    raspy.begin(115200);
    
    // pino do servo motor 
    clawServo.attach(11);

    // configura os motores
    Tortuga.motorsConfiguration();
}

void loop() {
    Tortuga.moveRight(1500);
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
*/

// lalalalala