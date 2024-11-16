#include <advanced-transportation-test-II.h>
#include <Setup.h>

#define red_cube_lowest1 6
#define red_cube_lowest2 13
#define blue_cube_lowest1 7
#define blue_cube_lowest2 15

#define inclineTablecube1 25
#define inclineTablecube2 26

#define precisionTableCube1 17
#define precisionTableCube2 21

#define loucos

void levarAoContainer(){
    //encontra a linha central
    while(1){
        while(1){
            Tortuga.moveLeft(50);
            int leftSensorColorBlue = LeftFloorSensor.colorRead('b', 100);
            int leftSensorColorRed = LeftFloorSensor.colorRead('r', 100);
            if(leftSensorColorBlue > 2*leftSensorColorRed){
                Tortuga.stop();
                break;
            }
        }
    }

    Tortuga.moveLeft(30);
    Tortuga.moveBackward(730);
    Tortuga.rotateAntiClockwise(562);
    
    //percorre a linha central
    int contadorDepassos = 0;
    while(1){
        Tortuga.moveForward(150);
        contadorDepassos++;
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
        
        // sai para o conteiner
        if(contadorDepassos > 26){
            Tortuga.stop();
            delay(2000);
            Tortuga.moveLeft(1200);
            //vai para esquerda ate a parede
            while(1){
                Tortuga.moveLeft(100);
                int leftDistance = usSensorLeft.getDistance();
                if(leftDistance <= 10){
                    Tortuga.moveRight(400);
                    break;
                }
            }
            // anda ate a mesa de conteiner e acha a altura
            while(1) {
                Tortuga.moveForward(150);
                int front_distance = usSensorFront.getDistance();
                if(front_distance <= 5) { // se alinha com a mesa
                    Tortuga.motorsConfiguration(300, 300);
                    Tortuga.moveForward(30);
                    Tortuga.motorsConfiguration(stepper_motors_velocity, stepper_motors_acceleration);
                    break;
                }
            }
            int conteiner_table_height = Tortuga.checkTableHeightFront();
            while(1){
              Tortuga.moveLeft(70);
              int leftDistance = usSensorLeft.getDistance();
              if(leftDistance < 10){
                Tortuga.moveRight(220);
                break;
              }  
            }
            Tortuga.placeCube(conteiner_table_height+5);
            
            Tortuga.moveBackward(1200);
            Tortuga.moveRight(1800);
            Tortuga.moveBackward(3500);
            Tortuga.rotateAntiClockwise(562);
        }   
    }
}

void levarInclinada(){
    //encontra a linha central
    while(1){
        Tortuga.moveLeft(50);
        int leftSensorColorBlue = LeftFloorSensor.colorRead('b', 100);
        int leftSensorColorRed = LeftFloorSensor.colorRead('r', 100);
        if(leftSensorColorBlue > 2*leftSensorColorRed){
            Tortuga.stop();
            break;
        }
    }


    Tortuga.moveLeft(30);
    Tortuga.moveBackward(730);
    Tortuga.rotateAntiClockwise(562);
    
    //percorre a linha central
    int contadorDepassos = 0;
    while(1){
        Tortuga.moveForward(150);
        contadorDepassos++;
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
        
        // sai para a mesa inclinada
        if(contadorDepassos > 45){
            Tortuga.stop();
            delay(2000);
            Tortuga.rotateClockwise(562);
            //vai para esquerda ate a parede
            while(1){
                Tortuga.moveForward(100);
                int FrontDistance = usSensorFront.getDistance();
                if(FrontDistance <= 25){
                    Tortuga.moveForward(200);
                    Tortuga.stop();
                    delay(2000);
                    Tortuga.openClaw();
                    Tortuga.moveBackward(200);
                    Tortuga.defaultClawPosition();
                    break;
                }
            }
            break;
        }   
    }

    Tortuga.moveBackward(500);
    Tortuga.rotateClockwise(562);

    while(1){
        Tortuga.moveForward(150);
        contadorDepassos++;
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
        
        int frontDistance = usSensorFront.getDistance();
        if(frontDistance < 15){
            Tortuga.rotateAntiClockwise(562);
            break;
        }
    }              
}


void advancedTransportationTestII() {
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
        Tortuga.alignWithTag(red_cube_lowest1);
        Tortuga.getCubeFront(table_height);

        levarAoContainer();

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
        
        Tortuga.alignWithTag(red_cube_lowest2);
        Tortuga.getCubeFront(table_height);

        levarAoContainer();

        Tortuga.defaultClawPosition();

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

        Tortuga.alignWithTag(inclineTablecube1);
        Tortuga.getCubeFront(table_height);

        levarInclinada();

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

        Tortuga.alignWithTag(inclineTablecube1);
        Tortuga.getCubeFront(table_height);

        levarInclinada();

        Tortuga.stop();
        delay(10000);
    }
}
