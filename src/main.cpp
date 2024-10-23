#include <AccelStepper.h>
#include <UltrasonicSensor.h>
#include <InfraredSensor.h>
#include <ColorSensor.h>
#include <Servo.h>
#include <Arduino.h>
#include <SoftwareSerial.h>

// motores de passo
AccelStepper motor1(AccelStepper::DRIVER, 50, 52);
AccelStepper motor2(AccelStepper::DRIVER, 53, 51);
AccelStepper motor3(AccelStepper::DRIVER, 49, 47);
AccelStepper motor4(AccelStepper::DRIVER, 45, 43);

// sensores ultrassônicos
UltrasonicSensor usSensorFront(31, 33);
UltrasonicSensor usSensorRight(35, 37);
UltrasonicSensor usSensorLeft(39, 41);

// sensores infravermelho
InfraredSensor irSensorLFL(0, 2);
InfraredSensor irSensorLFC(0, 18);
InfraredSensor irSensorLFR(0, 19);


// sensor de cor da garra
ColorSensor clawSensor(30, 28, 24, 26, 22);

// motor servo da garra
Servo clawMotor();

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

    motor1.setMaxSpeed(200);  // Velocidade máxima em passos/segundo
    motor1.setAcceleration(200);  // Aceleração em passos/segundo^2
    
    motor2.setMaxSpeed(200);
    motor2.setAcceleration(200);

    motor3.setMaxSpeed(200);
    motor3.setAcceleration(200);

    motor4.setMaxSpeed(200);
    motor4.setAcceleration(200);

}

void loop() {
  while(true) {
    
    
    
    int LFL = irSensorLFL.checkNearby();
    int LFC = irSensorLFC.checkNearby();
    int LFR = irSensorLFR.checkNearby();
    int frontDistance = usSensorFront.getDistance();
    moveForward(10);

    if (frontDistance < 15) {
      moveLeft(200);
      moveForward(370);
      while (true) {
        int LFR = irSensorLFR.checkNearby();
        moveRight(200);
        break;
        /*if (LFR == 1) {
          break;
        }*/
      }
    }

    /*

    if (LFL == 0 && LFC == 1 && LFR == 0) {
      moveForward(15);
    }

    if (LFL == 1 && LFC == 0 && LFR == 0) {
      moveForward(5);
      rotateClockwise(10);
    }

    if (LFL == 0 && LFC == 0 && LFR == 1) {
      moveForward(5);
      rotateAntiClockwise(10);
    }

    if (LFL == 0 && LFC == 0 && LFR == 0) {
      moveForward(10);
    }

    if (LFL == 1 && LFC == 1 && LFR == 1) {
      moveBackward(490);
    }
    */
  }

  }



