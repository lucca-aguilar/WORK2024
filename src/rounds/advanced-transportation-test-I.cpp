#include <advanced-transportation-test-I.h>
#include <Setup.h>

void levarAoContainer(int table_height){
    //encontra a linha central
    while(1){
        while(1){
            Tortuga.moveLeft(70);
            int leftSensorColorBlue = LeftFloorSensor.colorRead('b', 100);
            int leftSensorColorRed = LeftFloorSensor.colorRead('r', 100);
            if(leftSensorColorBlue > 2*leftSensorColorRed){
                Tortuga.stop();
                break;
            }
        }
    }

    Tortuga.moveLeft(40);
    Tortuga.moveBackward(730);
    Tortuga.rotateAntiClockwise(562);
    
    //percorre a linha central

    while(1){
        Tortuga.moveForward(150);
        int leftSensorColorBlue = LeftFloorSensor.colorRead('b', 100);
        int leftSensorColorRed = LeftFloorSensor.colorRead('r', 100);
        int rightSensorColorBlue = RightFloorSensor.colorRead('b', 100);
        int rightSensorColorRed = RightFloorSensor.colorRead('r', 100);

        if(leftSensorColorBlue > 1.8*leftSensorColorRed){
            Tortuga.rotateAntiClockwise(40);
        }
        if(rightSensorColorBlue > 1.8*rightSensorColorRed){
            Tortuga.rotateClockwise(40);
        }
    }
}

void levarAinclinada(){

}


void advancedTransportationTestI() {
    // variáveis globais
    int cube_counter = 0;
    int cube_found = 0;
    int right_distace_cubes = 0;

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

        // verifica a altura da mesa e pega o cubo 
        int table_height = Tortuga.checkTableHeightFront();    
        Tortuga.checkForCubeFront(table_height, 1000);
        Tortuga.getCubeFront(table_height);

        int id = 1;
        //pega o id

        switch(id){
            case 1:
                levarAoContainer(table_height);
                break;

            case 2:
                levarAinclinada();
            break;
        }
            


    }
}
