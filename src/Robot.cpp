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
#define velocity 100
#define acceleration 5

// construtor da classe robot

Robot::Robot(AccelStepper& motor1, AccelStepper& motor2, AccelStepper& motor3, AccelStepper& motor4, UltrasonicSensor& usSensorFront, UltrasonicSensor& usSensorRight, UltrasonicSensor& usSensorLeft, InfraredSensor& irSensorLFR, InfraredSensor& irSensorLFC, InfraredSensor& irSensorLFL, InfraredSensor& irSensorTableHeight1, InfraredSensor& irSensorTableHeight2, InfraredSensor& irSensorTableHeight3, InfraredSensor& irSensorTableHeight4, Servo& clawServo, ColorSensor& clawSensor, LED& blueLED, LED& redLED, SoftwareSerial& raspy, Bumper& clawBumper) : motor1(motor1), motor2(motor2), motor3(motor3), motor4(motor4), usSensorFront(usSensorFront), usSensorRight(usSensorRight), usSensorLeft(usSensorLeft), irSensorLFR(irSensorLFR), irSensorLFC(irSensorLFC), irSensorLFL(irSensorLFL), irSensorTableHeight1(irSensorTableHeight1), irSensorTableHeight2(irSensorTableHeight2), irSensorTableHeight3(irSensorTableHeight3), irSensorTableHeight4(irSensorTableHeight4), clawServo(clawServo), clawSensor(clawSensor), blueLED(blueLED), redLED(redLED), raspy(raspy), clawBumper(clawBumper) {}

// metodos envolvendo motores de passo (movimentacao)
void Robot::motorsConfiguration(){
    motor1.setMaxSpeed(velocity);  // velocidade maxima em passos/segundo
    motor1.setAcceleration(acceleration);  // aceleracao em passos/segundo^2
    
    motor2.setMaxSpeed(velocity);
    motor2.setAcceleration(acceleration);

    motor3.setMaxSpeed(velocity);
    motor3.setAcceleration(acceleration);

    motor4.setMaxSpeed(velocity);
    motor4.setAcceleration(acceleration);
};

void Robot::moveForward(int steps) {
    motor1.move(-steps);
    motor3.move(-steps);

    while (motor1.distanceToGo() != 0 || motor2.distanceToGo() != 0 || motor3.distanceToGo() != 0 || motor4.distanceToGo() != 0) {
    motor1.run();
    motor3.run();
  }
};

void Robot::moveBackward(int steps) {
    motor1.move(steps);
    motor3.move(steps);

    while (motor1.distanceToGo() != 0 || motor2.distanceToGo() != 0 || motor3.distanceToGo() != 0 || motor4.distanceToGo() != 0) {
        motor1.run();
        motor3.run();
    }
};

void Robot::moveLeft(int steps) {
    motor2.move(steps);
    motor4.move(steps);

    while (motor1.distanceToGo() != 0 || motor2.distanceToGo() != 0 || motor3.distanceToGo() != 0 || motor4.distanceToGo() != 0) {
        motor2.run();
        motor4.run();
    }
};

void Robot::moveRight(int steps) {
    motor2.move(-steps);
    motor4.move(-steps);

    while (motor1.distanceToGo() != 0 || motor2.distanceToGo() != 0 || motor3.distanceToGo() != 0 || motor4.distanceToGo() != 0) {
        motor2.run();
        motor4.run();
    }
};

void Robot::rotateClockwise(int steps) {
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

void Robot::rotateAntiClockwise(int steps) {
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

void Robot::stop(){ 
    // para todos os motores
    motor1.stop();
    motor2.stop();
    motor3.stop();
    motor4.stop();
};

// metodos envolvendo motores da garra

void Robot::openClaw(){
    clawServo.write(80);
};

void Robot::closeClaw(){
    clawServo.write(100);
};

void Robot::moveClaw(int clawHeight){

};

// metodos envolvendo sensores
int Robot::checkTableHeight(){

    /*para descobrir a altura de uma mesa, ja estando em frente a ela, o robo realiza os seguintes passos:
    1- realiza a leitura dos sensores no ponto "central" 
    2- move-se para a esquerda e realiza a leitura novamente
    3- move-se para a direita e realiza a leitura mais uma vez
    4- a altura e a media das tres alturas verificadas
    */

    int averageTableHeight;
    int tableHeight[3], sensorsReadings[4];

    for (int counter = 0; counter < 3; counter++) {
        // leituras dos sensores infravermelho
        sensorsReadings[0] = irSensorTableHeight1.measureDistance();
        sensorsReadings[1] = irSensorTableHeight2.measureDistance();
        sensorsReadings[2] = irSensorTableHeight3.measureDistance();
        sensorsReadings[3] = irSensorTableHeight4.measureDistance();

        if (sensorsReadings[0] < 50 && sensorsReadings[1] > 100 && sensorsReadings[2] > 100 && sensorsReadings[3] > 100) {
            tableHeight[counter] = 5;
        }
        if (sensorsReadings[0] < 50 && sensorsReadings[1] < 50 && sensorsReadings[2] > 100 && sensorsReadings[3] > 100) {
            tableHeight[counter] = 10;
        }
        if (sensorsReadings[0] < 50 && sensorsReadings[1] < 50 && sensorsReadings[2] < 50 && sensorsReadings[3] > 100) {
            tableHeight[counter] = 15;
        }

        if (counter == 0) {
            moveLeft(15);
        } 

        if (counter == 1) {
            moveRight(30);
        }
    }

    averageTableHeight = (tableHeight[0] + tableHeight[1] + tableHeight[2]) / 3;
    return averageTableHeight;
};

int Robot::checkForCube(int tableHeight){
    /*para verificar a presenca de um cubo sobre uma mesa, o robo segue os seguintes passos:
    1- se movimenta ate o ponto mais a direita da mesa, verificando com o sensor ultrassonico
    2- se movimenta para a esquerda e le com o sensor acima da altura da mesa
    3- quando a leitura desse sensor e satisfatoria, para em frente ao cubo
    */

   while (1) {
        int frontDistance = usSensorFront.getDistance();
        moveRight(10);
        if (frontDistance > 15) {
            stop();
            break;
        }
   }

   while (1) {
        int topSensorReading;
        if (tableHeight == 5) {
            topSensorReading = irSensorTableHeight3.measureDistance();
            if (topSensorReading < 100) {
                stop();
                break;
            }
        }

        if (tableHeight == 10) {
            topSensorReading = irSensorTableHeight2.measureDistance();
            if (topSensorReading < 100) {
                stop();
                break;
            }
        }

        if (tableHeight == 15) {
            topSensorReading = irSensorTableHeight1.measureDistance();
            if (topSensorReading < 100) {
                stop();
                break;
            }
        }
   }
    
};

// metodos dos sensores infravermelhos de segue linha
void Robot::followLine() {
    while (1) {
        int leftReading = irSensorLFL.measureDistance();
        int centerReading = irSensorLFC.measureDistance();
        int rightReading =  irSensorLFR.measureDistance();
    }
    
    
}

void Robot::alignInLine() {
    
}

// metodos envolvendo sensores ultrassonicos

// metodos envolvendo visao