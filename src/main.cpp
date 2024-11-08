// depois podemos tirar todas as outras bibliotecas e deixar apenas setup e os rounds :)
// bibliotecas de componentes
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

// biblioteca de setup
#include <Setup.h>

// bibliotecas de rounds
#include <advanced-manipulation-test.h>
#include <advanced-transportation-test-I.h>
#include <advanced-transportation-test-II.h>
#include <basic-manipulation-test.h>
#include <basic-transportation-test-I.h>
#include <basic-transportation-test-II.h>
#include <finals.h>

void setup() {
}

void loop() {
  basicManipulationTest();

  // funcoes para cada rodada, vai ficar comentado por enquanto  
  /*
  int round = 1; // Altere o número da rodada conforme necessário

    switch (round) {
        case 1:
            basicManipulationTestI();
            break;
        case 2:
            basicTransportationTestI();
            break;
        case 3:
            basicTransportationTestII();
            break;
        case 4:
            advancedManipulationTest();
        case 5:
            advancedTransportationTestI();
        case 6:
            advancedTransportationTestII();
        case 7:
            finals();
        default:
            Serial.println("Rodada inválida.");
            break;
    }

    delay(1000); // Pausa para evitar execuções muito rápidas
  */
}

// comentado - testes recorrentes
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