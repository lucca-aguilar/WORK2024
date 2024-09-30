#include <AccelStepper.h>

// Definição dos pinos para os 4 motores
#define DIR_MOTOR1 53
#define STEP_MOTOR1 51
#define DIR_MOTOR2 50
#define STEP_MOTOR2 52
#define DIR_MOTOR3 47
#define STEP_MOTOR3 49
#define DIR_MOTOR4 45
#define STEP_MOTOR4 43

// Criar instâncias da biblioteca AccelStepper para cada motor
AccelStepper motor1(AccelStepper::DRIVER, STEP_MOTOR1, DIR_MOTOR1);
AccelStepper motor2(AccelStepper::DRIVER, STEP_MOTOR2, DIR_MOTOR2);
AccelStepper motor3(AccelStepper::DRIVER, STEP_MOTOR3, DIR_MOTOR3);
AccelStepper motor4(AccelStepper::DRIVER, STEP_MOTOR4, DIR_MOTOR4);

void setup() {
  // Definir a velocidade máxima e aceleração para cada motor
  motor1.setMaxSpeed(100);  // Velocidade máxima em passos/segundo
  motor1.setAcceleration(100);  // Aceleração em passos/segundo^2
  
  motor2.setMaxSpeed(100);
  motor2.setAcceleration(100);

  motor3.setMaxSpeed(100);
  motor3.setAcceleration(100);

  motor4.setMaxSpeed(100);
  motor4.setAcceleration(100);
}

void moveForward(int steps) {
  // Motores 1 e 4 giram em um sentido, 2 e 3 no sentido oposto
  motor2.move(steps);
  motor3.move(steps);
}

void moveBackward(int steps) {
  // Motores 1 e 4 giram no sentido oposto, 2 e 3 no sentido contrário
  motor2.move(-steps);
  motor3.move(-steps);
}

void loop() {

  // Mover 10 cm para trás
  moveBackward(2500);

  while (motor1.distanceToGo() != 0 || motor2.distanceToGo() != 0 || motor3.distanceToGo() != 0 || motor4.distanceToGo() != 0) {
    motor1.run();
    motor2.run();
    motor3.run();
    motor4.run();
  }

  // Mover 10 cm para frente
  moveForward(2500);

  while (motor1.distanceToGo() != 0 || motor2.distanceToGo() != 0 || motor3.distanceToGo() != 0 || motor4.distanceToGo() != 0) {
    motor1.run();
    motor2.run();
    motor3.run();
    motor4.run();
  }

  delay(1000);  // Pausa de 1 segundo
}
