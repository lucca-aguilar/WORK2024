#include <AccelStepper.h>
#include <Arduino.h>
#include <Bumper.h>
#include <ColorSensor.h>
#include <InfraredSensor.h>
#include <LED.h>
#include <MotorDC.h>
#include <Robot.h>
#include <Servo.h>
#include <UltrasonicSensor.h>
#define true 0
#define false 1
#define dc_velocity 255
#define stepper_motors_velocity 800
#define stepper_motors_acceleration 800

// construtor da classe robot

// metodos de configuraçao
void Robot::serialConfiguration() {
    Serial.begin(9600);
};

void Robot::servoConfiguration() {
    clawServo.attach(7);
};

void Robot::motorsConfiguration(int velocity, int acceleration) {
    motor1.setMaxSpeed(velocity);  // velocidade maxima em passos/segundo
    motor1.setAcceleration(acceleration);  // aceleracao em passos/segundo^2

    motor2.setMaxSpeed(velocity);
    motor2.setAcceleration(acceleration);

    motor3.setMaxSpeed(velocity);
    motor3.setAcceleration(acceleration);

    motor4.setMaxSpeed(velocity);
    motor4.setAcceleration(acceleration);
};

// metodos mais gerais
int Robot::cubePresence() {
    if (clawBumper.checkCube() == true) {
        return true;
    } else {
        return false;
    }
};

void Robot::getCubeFront(int table_height) {
    // abre a garra
    clawServo.writeMicroseconds(1300); //1300
    delay(1500);
    clawServo.writeMicroseconds(1500); //1500

    if (table_height == 5) {
        moveBackward(300);
        moveClawDown(40);
        moveForward(270);
    }

    if (table_height == 10) {
        moveBackward(300);
        moveClawDown(35);
        moveForward(270);
    }

    if (table_height == 15) {
        moveBackward(300);
        moveClawDown(30);
        moveForward(270);
    }

    defaultClawPosition();
};

void Robot::getCubeBack(int table_height) {
    // abre a garra
    clawServo.writeMicroseconds(1300); //1300
    delay(1500);
    clawServo.writeMicroseconds(1500); //1500

    if (table_height == 5) {
        moveBackward(300);
        moveRight(100);
        moveClawDown(34);
        moveForward(270);
    }

    if (table_height == 10) {
        moveBackward(300);
        moveRight(100);
        moveClawDown(29);
        moveForward(270);
    }

    if (table_height == 15) {
        moveBackward(300);
        moveRight(100);
        moveClawDown(24);
        moveForward(270);
    }

    defaultClawPosition();
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

// Rotacao 360 graus = 2250 passos
void Robot::rotateClockwise(int steps) {
    motor1.move(steps);
    motor2.move(steps);
    motor3.move(steps);
    motor4.move(steps);

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
    motor3.move(-steps);
    motor4.move(-steps);

    while (motor1.distanceToGo() != 0 || motor2.distanceToGo() != 0 || motor3.distanceToGo() != 0 || motor4.distanceToGo() != 0) {
        motor1.run();
        motor2.run();
        motor3.run();
        motor4.run();
    }
};

void Robot::stop() {
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
    clawMotor.moveForward(255);
    delay(10000);
};

void Robot::moveClawDown(int dc_dislocation) {
    int dc_time = 0;
    dc_time = ((dc_dislocation + 7 - 1.5375) / 4.5) * 1000;
    clawMotor.moveBackward(255);
    delay(dc_time);
    clawMotor.stop();
};

void Robot::defaultClawPosition() {
    // fecha a garra
    clawServo.writeMicroseconds(1700);
    delay(1200);
    clawServo.writeMicroseconds(1500);

    // volta a garra para cima
    clawMotor.moveForward(255);
    delay(8000);
    clawMotor.stop();
};

void Robot::placeCube(int height){
    moveClawDown(39 - height);

    // abre a garra
    clawServo.writeMicroseconds(1300);
    delay(1200);
    clawServo.writeMicroseconds(1500);

    // volta a garra para cima
    clawMotor.moveForward(255);
    delay(8000);

    // fecha a garra
    clawServo.writeMicroseconds(1700);
    delay(1200);
    clawServo.writeMicroseconds(1500);
};

// metodos envolvendo sensores
int Robot::checkTableHeightFront() {

    /*para descobrir a altura de uma mesa, ja estando em frente a ela, o robo realiza os seguintes passos:
    1- realiza a leitura dos sensores no ponto "central" 
    2- move-se para a esquerda e realiza a leitura novamente
    3- move-se para a direita e realiza a leitura mais uma vez
    4- a altura e a media das tres alturas verificadas
    */
    int irThreshold = 950;
    int tableHeight[3], sensorsReadings[4];

    for (int counter = 0; counter < 3; counter++) {
        // leituras dos sensores infravermelho
        sensorsReadings[0] = 0;
        sensorsReadings[1] = 0;
        sensorsReadings[2] = 0;
        sensorsReadings[3] = 0;

        sensorsReadings[0] = irSensorTableHeight1.measureDistance();
        sensorsReadings[1] = irSensorTableHeight2.measureDistance();
        sensorsReadings[2] = irSensorTableHeight3.measureDistance();
        sensorsReadings[3] = irSensorTableHeight4.measureDistance();

        if (sensorsReadings[3] < irThreshold && sensorsReadings[2] > irThreshold && sensorsReadings[1] > irThreshold && sensorsReadings[0] > irThreshold) {
            tableHeight[counter] = 5;
        }
        if (sensorsReadings[3] < irThreshold && sensorsReadings[2] < irThreshold && sensorsReadings[1] > irThreshold && sensorsReadings[0] > irThreshold) {
            tableHeight[counter] = 10;
        }
        if (sensorsReadings[3] < irThreshold && sensorsReadings[2] < irThreshold && sensorsReadings[1] < irThreshold && sensorsReadings[0] > irThreshold) {
            tableHeight[counter] = 15;
        }

        if (counter == 0) {
            moveLeft(200);
        }

        if (counter == 1) {
            moveRight(300);
        }
    }

    int smallerTableHeight = 15;
    for (int i = 0; i < 3; i++) {
        if (tableHeight[i] <= smallerTableHeight) {
            smallerTableHeight = tableHeight[i];
        }
    }
    return smallerTableHeight;
};

int Robot::checkForCubeFront(int tableHeight, int ir1) {
    /*para verificar a presenca de um cubo sobre uma mesa, o robo segue os seguintes passos:
    1- se movimenta ate o ponto mais a direita da mesa, verificando com o sensor ultrassonico
    2- se movimenta para a esquerda e le com o sensor acima da altura da mesa
    3- quando a leitura desse sensor e satisfatoria, para em frente ao cubo
    */
    int irThreshold = ir1 - (0.05 * ir1);
    int cubeFound = 0;
    
    while(1){
        int rightDistance = usSensorRight.getDistance();
        if(rightDistance >= 7){
            moveRight(70);
        }else{
            stop();
            break;
        }
    }
   
    while(1){
        int topSensorReading;
        moveLeft(70);

        if(tableHeight == 5){
            topSensorReading = irSensorTableHeight3.measureDistance();
            if(topSensorReading <= irThreshold){
                stop();
                cubeFound = 1;
                return cubeFound;
            }
        }

        if(tableHeight == 10){
            topSensorReading = irSensorTableHeight2.measureDistance();
            if(topSensorReading <= irThreshold){
                stop();
                cubeFound = 1;
                return cubeFound;
            }
        }

        if(tableHeight == 15){
            topSensorReading = irSensorTableHeight1.measureDistance();
            if (topSensorReading <= irThreshold) {
                stop();
                cubeFound = 1;
                return cubeFound;
            }
            
        }

        int frontDistance = usSensorFront.getDistance();
        if(frontDistance > 15){
            stop();
            return cubeFound;
        }
    }
};

int Robot::checkForCubeBack(int tableHeight, int ir1) {
    /*para verificar a presenca de um cubo sobre uma mesa, o robo segue os seguintes passos:
    1- se movimenta ate o ponto mais a direita da mesa, verificando com o sensor ultrassonico
    2- se movimenta para a esquerda e le com o sensor acima da altura da mesa
    3- quando a leitura desse sensor e satisfatoria, para em frente ao cubo
    */
    int irThreshold = ir1 - (0.05 * ir1);
    int cubeFound = 0;
    
    while(1){
        int leftDistance = usSensorLeft.getDistance();
        if(leftDistance >= 7){
            moveLeft(70);
        }else{
            stop();
            break;
        }
    }

    while(1){
        int topSensorReading;
        moveRight(70);

        if(tableHeight == 5){
            topSensorReading = irSensorTableHeight3.measureDistance();
            if(topSensorReading <= irThreshold){
                stop();
                cubeFound = 1;
                return cubeFound;
            }
        }

        if(tableHeight == 10){
            topSensorReading = irSensorTableHeight2.measureDistance();
            if(topSensorReading <= irThreshold){
                stop();
                cubeFound = 1;
                return cubeFound;
            }
        }

        if(tableHeight == 15){
            topSensorReading = irSensorTableHeight1.measureDistance();
            if (topSensorReading <= irThreshold) {
                stop();
                cubeFound = 1;
                return cubeFound;
            }
            
        }
        
        int frontDistance = usSensorFront.getDistance();
        if(frontDistance > 15){
            stop();
            return cubeFound;
        }
    }
};

// metodos envolvendo sensor de cor
char Robot::checkCubeColor() {
    int red_value = clawSensor.colorRead('r', 100);
    int green_value = clawSensor.colorRead('g', 100);
    int blue_value = clawSensor.colorRead('b', 100);
    delay(1000);

    if (red_value > 1.3*green_value) {
        return 'R';
    } else {
        return 'B';
    }
};

char Robot::checkFloorColor() {
    int red_value = RightFloorSensor.colorRead('r', 100);
    int green_value = RightFloorSensor.colorRead('g', 100);
    int blue_value = RightFloorSensor.colorRead('b', 100);
    delay(1000);

    if (blue_value > 2*red_value) {
        return 'B';
    } else {
        return 'W';
    }
};

// metodos envolvendo visao
int Robot::checkVirtualWall() {
    // envia comando para a raspy
    Serial.println('W');

    if (Serial.available() > 0) {
        char command = Serial.read(); // le mensagem recebida
        delay(100);

        if (command == 'Y') {
            return true;
        }

        if (command == 'N') {
            return false;
        }
    } 
};

int Robot::virtualWallDistance() {
    // envia comando para a raspy
    Serial.write('D');
    delay(100);

    if (Serial.available() > 0) {
        int virtual_wall_distance = Serial.parseInt(); // le mensagem recebida
        return virtual_wall_distance;
    }
};

int Robot::readTag() {
    int detected_tag = 0;
    while (Serial.available() < 1) {
        char flush = Serial.read();
    }
    Serial.clearWriteError();
    Serial.write('A'); 
    String detected_tag_string = Serial.readStringUntil('\n');
    detected_tag = detected_tag_string.toInt();
    return detected_tag;
};

void Robot::findTag(int key_tag) {
    int detected_tag = 0;
    while (1) {
        moveLeft(30);
        detected_tag = readTag();
        if (detected_tag == key_tag) {
            Serial.write('S');
            stop();
            break;
        }
    }
};

int Robot::alignWithTag(int key_tag) {
    // Encontra a tag
    findTag(key_tag);

    rgbLED.blue();
    delay(500);
    rgbLED.off();
    delay(500);
    rgbLED.blue();
    delay(500);
    rgbLED.off();
    delay(500);

    // Se uma tag foi encontrada, ajustar para alinhamento
    moveLeft(70);
};


