#include <basic-transportation-test-I.h>
#include <Setup.h>

// definições de algumas funções úteis
void goToTableBack() {
    Tortuga.moveLeft(850);
    Tortuga.moveForward(1800);
    Tortuga.rotateClockwise(1110);
}

void goToLineFront() {
    Tortuga.moveLeft(600);
    Tortuga.rotateAntiClockwise(1124);
    while(1) {
        Tortuga.moveForward(70);
        char floor_color = Tortuga.checkFloorColor();
        if (floor_color == 'B') {
            Tortuga.stop();
            break;
        }
    }
}

void goToLineBack() {
    Tortuga.moveRight(300);
    while(1) {
        Tortuga.moveForward(70);
        char floor_color = Tortuga.checkFloorColor();
        if (floor_color == 'B') {
            Tortuga.stop();
            break;
        }
    }
}

void goToStackingZone() {
    Tortuga.moveBackward(700);
    Tortuga.rotateClockwise(562);
    Tortuga.moveForward(1200);
    while(1) {
        Tortuga.moveForward(70);
        char floor_color = Tortuga.checkFloorColor();
        if (floor_color == 'B') {
            Tortuga.stop();
            break;
        }
    }
}

int defineHeight(int cube_counter) {
    if (cube_counter == 1) {
        return 5;
    } 

    if (cube_counter == 2) {
        return 10;
    }

    if (cube_counter == 3) {
        return 15;
    }

    if (cube_counter == 4) {
        return 20;
    }
}

void basicTransportationTestI() {
    // variáveis globais
    int cube_counter = 0;
    int cube_found = 0;

    while(1) {
        // coloca a garra nas posicoes corretas
        Tortuga.defaultClawPosition();

        // anda até encontrar a mesa
        while(1) {
            Tortuga.moveForward(150);
            int front_distance = usSensorFront.getDistance();
            if (front_distance <= 5) { // se alinha com a mesa
                Tortuga.motorsConfiguration(300, 300);
                Tortuga.moveForward(30);
                Tortuga.motorsConfiguration(stepper_motors_velocity, stepper_motors_acceleration);
                break;
            }
        }

        // verifica a altura da mesa
        int table_height = Tortuga.checkTableHeightFront();

        // procura por cubos na frente
        cube_found = Tortuga.checkForCubeFront(table_height);
        if (cube_found == 1) {
            Tortuga.getCubeFront(table_height);
            cube_counter++;
            while(1){
                Tortuga.moveLeft(70);
                int FrontDistance = usSensorFront.getDistance();
                if(FrontDistance > 15){
                    Tortuga.moveLeft(400);
                    break;
                }
            }
            goToLineFront();
        } else {
            goToTableBack();
            cube_found = Tortuga.checkForCubeBack(table_height);
            if (cube_found == 1) {
                Tortuga.getCubeBack(table_height);
                cube_counter++;

                while(1){
                Tortuga.moveRight(70);
                int FrontDistance = usSensorFront.getDistance();
                if(FrontDistance > 15){
                    Tortuga.moveRight(400);
                    break;
                }
            }
                goToLineBack();
            } else {
                Tortuga.moveRight(560);
                Tortuga.moveForward(3000);
                Tortuga.rotateClockwise(562);
                Tortuga.moveForward(3000);
                Tortuga.rotateAntiClockwise(20);
                Tortuga.moveForward(1200);
                Tortuga.rotateAntiClockwise(562);
                Tortuga.moveForward(2000);
                delay(15000);
            }
        }

        // vai para a zona de empilhamento
        goToStackingZone();

        // coloca o cubo na pilha
        int height = defineHeight(cube_counter);
        Tortuga.placeCube(height);
        //voltar para mesa
        Tortuga.moveBackward(700);
        Tortuga.rotateClockwise(562);
        Tortuga.moveForward(300);
        while(1) {
            Tortuga.moveForward(70);
            char floor_color = Tortuga.checkFloorColor();
            if (floor_color == 'B') {
                Tortuga.stop();
                break;
            }
        }   

    }
}