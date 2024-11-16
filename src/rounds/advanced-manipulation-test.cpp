#include <advanced-manipulation-test.h>
#include <Setup.h>

void advancedManipulationTest() {
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
        Serial.println(table_height);      
        Tortuga.checkForCubeFront(table_height, 1000);
        Tortuga.getCubeFront(table_height);

        // ir para tras da mesa 
        while(1){
          Tortuga.moveLeft(70);
          int frontdistance = usSensorFront.getDistance();
          if( frontdistance > 15){
            Tortuga.stop();
            break;
          }
        }
        Tortuga.moveLeft(800);
        Tortuga.rotateClockwise(20);
        Tortuga.moveForward(1900);
        Tortuga.rotateClockwise(1125);
        Tortuga.moveLeft(1000);

        while(1){
            Tortuga.moveLeft(100);
            int leftDistance = usSensorLeft.getDistance();
            if(leftDistance <= 10){
              Tortuga.moveRight(450);
              Tortuga.rotateAntiClockwise(40);
                break;
            }
        }
        Tortuga.moveLeft(right_distace_cubes);
        Tortuga.placeCube(table_height);
        right_distace_cubes += 120;
        

        //ir para frente da mesa
        
        while(1){
          Tortuga.moveRight(70);
          int frontdistance = usSensorFront.getDistance();
          if( frontdistance > 15){
            Tortuga.moveRight(700);
            break;
          }
        }

        Tortuga.moveForward(2000);
        Tortuga.rotateClockwise(1125);
        Tortuga.moveRight(1700);
        Tortuga.rotateAntiClockwise(20);


        if(cube_counter == 5){
          break;
        }
        }
}