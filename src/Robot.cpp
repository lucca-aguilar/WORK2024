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
#define dc_velocity 255
#define stepper_motors_velocity 400
#define stepper_motors_acceleration 200

// construtor da classe robot
Robot::Robot(AccelStepper& motor1, AccelStepper& motor2, AccelStepper& motor3, AccelStepper& motor4, UltrasonicSensor& usSensorFront, UltrasonicSensor& usSensorRight, UltrasonicSensor& usSensorLeft, InfraredSensor& irSensorLFR, InfraredSensor& irSensorLFC, InfraredSensor& irSensorLFL, InfraredSensor& irSensorTableHeight1, InfraredSensor& irSensorTableHeight2, InfraredSensor& irSensorTableHeight3, InfraredSensor& irSensorTableHeight4, Servo& clawServo, ColorSensor& clawSensor, LED& blueLED, LED& redLED, SoftwareSerial& raspy, Bumper& clawBumper, MotorDC& clawMotor) : motor1(motor1), motor2(motor2), motor3(motor3), motor4(motor4), usSensorFront(usSensorFront), usSensorRight(usSensorRight), usSensorLeft(usSensorLeft), irSensorLFR(irSensorLFR), irSensorLFC(irSensorLFC), irSensorLFL(irSensorLFL), irSensorTableHeight1(irSensorTableHeight1), irSensorTableHeight2(irSensorTableHeight2), irSensorTableHeight3(irSensorTableHeight3), irSensorTableHeight4(irSensorTableHeight4), clawServo(clawServo), clawSensor(clawSensor), blueLED(blueLED), redLED(redLED), raspy(raspy), clawBumper(clawBumper), clawMotor(clawMotor) {}

// metodos de configuraçao
void Robot::serialConfiguration() {
    raspy.begin(115200);
};

void Robot::servoConfiguration() {
    clawServo.attach(7);
};

void Robot::motorsConfiguration(){
    motor1.setMaxSpeed(stepper_motors_velocity);  // velocidade maxima em passos/segundo
    motor1.setAcceleration(stepper_motors_acceleration);  // aceleracao em passos/segundo^2
    
    motor2.setMaxSpeed(stepper_motors_velocity);
    motor2.setAcceleration(stepper_motors_acceleration);

    motor3.setMaxSpeed(stepper_motors_velocity);
    motor3.setAcceleration(stepper_motors_acceleration);

    motor4.setMaxSpeed(stepper_motors_velocity);
    motor4.setAcceleration(stepper_motors_acceleration);
};

// metodos mais gerais
int Robot::cubePresence(){
    if (clawBumper.checkCube() == true) {
        return true;
    } else {
        return false;
    }
};

void Robot::getCube(int table_height) {

};

// metodos envolvendo motores de passo (movimentacao)
void Robot::moveForward(int steps) {
    motor1.move(-steps);
    motor3.move(steps);

    while (motor1.distanceToGo() != 0 || motor2.distanceToGo() != 0 || motor3.distanceToGo() != 0 || motor4.distanceToGo() != 0) {
    motor1.run();
    motor3.run();
  }
};

void Robot::moveBackward(int steps) {
    motor1.move(steps);
    motor3.move(-steps);

    while (motor1.distanceToGo() != 0 || motor2.distanceToGo() != 0 || motor3.distanceToGo() != 0 || motor4.distanceToGo() != 0) {
        motor1.run();
        motor3.run();
    }
};

void Robot::moveLeft(int steps) {
    motor2.move(-steps);
    motor4.move(steps);

    while (motor1.distanceToGo() != 0 || motor2.distanceToGo() != 0 || motor3.distanceToGo() != 0 || motor4.distanceToGo() != 0) {
        motor2.run();
        motor4.run();
    }
};

void Robot::moveRight(int steps) {
    motor2.move(steps);
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

void Robot::openClaw() {
    clawServo.write(80);
};

void Robot::closeClaw() {
    clawServo.write(100);
};

void Robot::moveClawUp(int dc_dislocation) {
    int dc_time;
    dc_time = dc_dislocation / dc_velocity;
    clawMotor.moveForward(dc_velocity);
    delay(dc_time);
};

void Robot::moveClawDown(int dc_dislocation) {
    int dc_time;
    dc_time = dc_dislocation / dc_velocity;
    clawMotor.moveBackward(dc_velocity);
    delay(dc_time);
};

// metodos envolvendo sensores
int Robot::checkTableHeight() {

    /*para descobrir a altura de uma mesa, ja estando em frente a ela, o robo realiza os seguintes passos:
    1- realiza a leitura dos sensores no ponto "central" 
    2- move-se para a esquerda e realiza a leitura novamente
    3- move-se para a direita e realiza a leitura mais uma vez
    4- a altura e a media das tres alturas verificadas
    */
    int irThreshold = 900;
    int tableHeight[3], sensorsReadings[4];

    for (int counter = 0; counter < 3; counter++) {
        // leituras dos sensores infravermelho
        sensorsReadings[0] = irSensorTableHeight1.measureDistance();
        sensorsReadings[1] = irSensorTableHeight2.measureDistance();
        sensorsReadings[2] = irSensorTableHeight3.measureDistance();
        sensorsReadings[3] = irSensorTableHeight4.measureDistance();

        if (sensorsReadings[4] < irThreshold && sensorsReadings[3] > irThreshold && sensorsReadings[2] > irThreshold && sensorsReadings[1] > irThreshold) {
            tableHeight[counter] = 5;
        }
        if (sensorsReadings[4] < irThreshold && sensorsReadings[3] < irThreshold && sensorsReadings[2] > irThreshold && sensorsReadings[1] > irThreshold) {
            tableHeight[counter] = 10;
        }
        if (sensorsReadings[4] < irThreshold && sensorsReadings[3] < irThreshold && sensorsReadings[2] < irThreshold && sensorsReadings[1] > irThreshold) {
            tableHeight[counter] = 15;
        }

        if (counter == 0) {
            moveLeft(135);
        } 

        if (counter == 1) {
            moveRight(270);
        }
    }

    int smallerTableHeight = 15;
    for (int i = 0; i < 3; i++) {
        if (tableHeight[i] <= smallerTableHeight) {
            smallerTableHeight = tableHeight[i];
        }
    }
    Serial.println("Table height:");
    Serial.println(smallerTableHeight);
    return smallerTableHeight;
};

void Robot::checkForCube(int tableHeight) {
    /*para verificar a presenca de um cubo sobre uma mesa, o robo segue os seguintes passos:
    1- se movimenta ate o ponto mais a direita da mesa, verificando com o sensor ultrassonico
    2- se movimenta para a esquerda e le com o sensor acima da altura da mesa
    3- quando a leitura desse sensor e satisfatoria, para em frente ao cubo
    */
   int irThreshold = 900;

   while (1) {
        int frontDistance = usSensorFront.getDistance();
        moveLeft(70);
        if (frontDistance > 10) {
            while (1) {
                int topSensorReading;
                if (tableHeight == 5) {
                    topSensorReading = irSensorTableHeight3.measureDistance();
                    if (topSensorReading < irThreshold) {
                        stop();
                        break;
                    }
                }

                if (tableHeight == 10) {
                    topSensorReading = irSensorTableHeight2.measureDistance();
                    if (topSensorReading < irThreshold) {
                        stop();
                        break;
                    }
                }

                if (tableHeight == 15) {
                    topSensorReading = irSensorTableHeight1.measureDistance();
                    if (topSensorReading < irThreshold) {
                        stop();
                        break;
                    }
                }
            }
        }
    }
};

        // metodos dos sensores infravermelhos de segue linha
        void Robot::followLine(int activator) {
            while (activator == true) {
                int leftReading = irSensorLFL.measureDistance();
                int centerReading = irSensorLFC.measureDistance();
                int rightReading =  irSensorLFR.measureDistance();

                if (centerReading > 900 && leftReading < 900 && centerReading < 900) {
                    moveForward(50);
                } else {
                    if (centerReading < 900 && leftReading > 900 && rightReading < 900) {
                        rotateAntiClockwise(50);
                    }
                    if (centerReading < 900 && leftReading < 900 && rightReading > 900) {
                        rotateClockwise(50);
                    }
                }
            }
};

// metodos envolvendo sensor de cor
char* Robot::checkCubeColor() {
    int red_value = clawSensor.colorRead('r', 20);
    int green_value = clawSensor.colorRead('g', 20);
    int blue_value = clawSensor.colorRead('b', 20);
    delay(1000);
    Serial.println(red_value);
    Serial.println(green_value);
    Serial.println(blue_value);

    if (red_value > blue_value && red_value > green_value) {
        return "Vermelho";
    } else if (blue_value > red_value && blue_value > green_value) {
        return "Azul";
    } else {
        return "";
    }
};

// metodos envolvendo visao
int Robot::checkVirtualWall() {
    // envia comando para a raspy
    raspy.println("Checar parede virtual");

    if (raspy.available() > 0) {
        String command = raspy.readString(); // le mensagem recebida
        delay(100);

        if (command == "Parede virtual detectada") {
            return true;
            // para debugar
            Serial.println("Fita detectada.");
        }

        if (command == "Parede virtual nao detectada") {
            return false;
            // para debugar
            Serial.println("Fita nao detectada");
        }
    } else {
        Serial.println("Raspy nao enviou nada");
    }
};

int Robot::virtualWallDistance() {
    // envia comando para a raspy
    raspy.println("Checar distancia da parede virtual");
    delay(100);

    if (raspy.available() > 0) {
        int virtual_wall_distance = raspy.parseInt(); // le mensagem recebida
        return virtual_wall_distance;
    } else {
        Serial.println("Raspy nao enviou nada");
    }
};

int Robot::readTag() {
    // envia comando para a raspy
    raspy.println("Checar AprilTag");
    delay(100);

    if (raspy.available() > 0) {
        int aprilTag = raspy.parseInt(); // le mensagem recebida
        return aprilTag;
    }  
};

char* Robot::checkConteinerColor() {
    // envia comando para a raspy
    raspy.println("Checar cor do conteiner");

    if (raspy.available() > 0) {
        String command = raspy.readString(); // le mensagem recebida
        delay(100);

        if (command == "Vermelho") {
            return "Vermelho";
            // para debugar
            Serial.println("Vermelho");
        }

        if (command == "Azul") {
            return "Azul";
            // para debugar
            Serial.println("Azul");
        }
    } else {
        Serial.println("Raspy nao enviou nada");
    }
}; 