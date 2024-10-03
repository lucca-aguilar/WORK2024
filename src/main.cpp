#include <AccelStepper.h>
#include <UltrasonicSensor.h>
#include <InfraredSensor.h>
#include <Arduino.h>
#include <SoftwareSerial.h>

// motores
AccelStepper motor1(AccelStepper::DRIVER, 53, 53);
AccelStepper motor2(AccelStepper::DRIVER, 52, 50);
AccelStepper motor3(AccelStepper::DRIVER, 20, 21);
AccelStepper motor4(AccelStepper::DRIVER, 43, 45);

// sensores ultrassônicos
UltrasonicSensor usSensorFront(31, 33);
UltrasonicSensor usSensorRight(35, 37);
UltrasonicSensor usSensorLeft(39, 41);

// sensores infravermelho
InfraredSensor irSensorLFL(0, 2);
InfraredSensor irSensorLFC(0, 19);
InfraredSensor irSensorLFR(0, 18);

void runForward() {
    motor2.move(-10000);
    motor3.move(-10000);

    while (motor1.distanceToGo() != 0 || motor2.distanceToGo() != 0 || motor3.distanceToGo() != 0 || motor4.distanceToGo() != 0) {
    motor2.run();
    motor3.run();
  }
};

void runBackward() {
    motor2.move(10000);
    motor3.move(10000);

    while (motor1.distanceToGo() != 0 || motor2.distanceToGo() != 0 || motor3.distanceToGo() != 0 || motor4.distanceToGo() != 0) {
    motor2.run();
    motor3.run();
  }
}

void moveForward(int steps) {
    motor2.move(-steps);
    motor3.move(-steps);

    while (motor1.distanceToGo() != 0 || motor2.distanceToGo() != 0 || motor3.distanceToGo() != 0 || motor4.distanceToGo() != 0) {
    motor2.run();
    motor3.run();
  }
};

void moveBackward(int steps) {
    motor2.move(steps);
    motor3.move(steps);

    while (motor1.distanceToGo() != 0 || motor2.distanceToGo() != 0 || motor3.distanceToGo() != 0 || motor4.distanceToGo() != 0) {
        motor2.run();
        motor3.run();
    }
};

void moveLeft(int steps) {
    motor1.move(steps);
    motor4.move(steps);

    while (motor1.distanceToGo() != 0 || motor2.distanceToGo() != 0 || motor3.distanceToGo() != 0 || motor4.distanceToGo() != 0) {
        motor1.run();
        motor4.run();
    }
};

void moveRight(int steps) {
    motor1.move(-steps);
    motor4.move(-steps);

    while (motor1.distanceToGo() != 0 || motor2.distanceToGo() != 0 || motor3.distanceToGo() != 0 || motor4.distanceToGo() != 0) {
        motor1.run();
        motor4.run();
    }
};

void rotateClockwise(int steps) {
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

void rotateAntiClockwise(int steps) {
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

void setup() {
    Serial.begin(9600);

    motor1.setMaxSpeed(100);  // Velocidade máxima em passos/segundo
    motor1.setAcceleration(200);  // Aceleração em passos/segundo^2
    
    motor2.setMaxSpeed(100);
    motor2.setAcceleration(200);

    motor3.setMaxSpeed(115);
    motor3.setAcceleration(200);

    motor4.setMaxSpeed(100);
    motor4.setAcceleration(200);
}

void loop() {
  /*
  while (1) {
    runForward();
    int frontDistance = usSensorFront.getDistance();
    if (frontDistance < 30) {
      break;
    }
  }

  moveLeft(300);
  moveForward(300);
  moveRight(300);
  */

  bool boolLeft = irSensorLFL.checkNearby();
  bool boolCenter = irSensorLFC.checkNearby();
  bool boolRight = irSensorLFR.checkNearby();

  Serial.print(boolLeft);
  Serial.print(" ");
  Serial.print(boolCenter);
  Serial.print(" ");
  Serial.print(boolRight);
  Serial.println();

  /*
  int distanceFront = usSensorFront.getDistance();
  int distanceLeft = usSensorLeft.getDistance();
  int distanceRight = usSensorRight.getDistance();

  Serial.print(distanceFront);
  Serial.print(" ");
  Serial.print(distanceLeft);
  Serial.print(" ");
  Serial.print(distanceRight);
  Serial.println();
  */

}
