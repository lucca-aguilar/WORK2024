#include <basic-manipulation-test.h>
#include <Setup.h>

void basicManipulationTest() {
    int cube_counter = 0;
    Serial.println("Entrou na função");
    while(true) {
        // variaveis globais
        Serial.println("Definiu variaveis");

        // coloca a garra nas posicoes corretas
        Tortuga.defaultClawPosition();
        Serial.println("garra inicial");

        while (true) { // anda ate encontrar a mesa
            Tortuga.moveForward(150);
            int front_distance = usSensorFront.getDistance();
            if (front_distance <= 5) { // se alinha com a mesa
                Tortuga.motorsConfiguration(300, 300);
                Tortuga.moveForward(100);
                Tortuga.motorsConfiguration(stepper_motors_velocity, stepper_motors_acceleration);
                break;
            }
        }
        Serial.println("encontrou a mesa");

        // verifica altura da mesa
        int table_height = Tortuga.checkTableHeightFront();

        // escaneia em busca de um cubo pela frente
        int cubeFound = Tortuga.checkForCubeFront(table_height);
        Serial.println("cubefound is " + cubeFound);

        if(cubeFound == 1){ // pega o cubo, caso encontre
          Tortuga.getCubeFront(table_height); //confirmacao que pegou o cubo
          char cube_color = Tortuga.checkCubeColor();
          if (cube_color == 'B') { // mostra a cor do cubo
            rgbLED.blue();
            rgbLED.off();
          } else {
            rgbLED.red();
            rgbLED.off();
          }
          cube_counter++; // aumenta a contagem de cubos
          Tortuga.moveBackward(800);
          Tortuga.rotateAntiClockwise(570);
        }

        if(cubeFound == 0){ // se não encontrou, procura na parte de trás da mesa
          Tortuga.moveLeft(850);
          Tortuga.moveForward(1800);
          Tortuga.rotateClockwise(1135);
          Tortuga.moveLeft(850);

          while (true) { // anda ate encontrar a mesa
            Tortuga.moveForward(150);
            int front_distance = usSensorFront.getDistance();
            if (front_distance <= 5) { // se alinha com a mesa
                Tortuga.motorsConfiguration(300, 300);
                Tortuga.moveForward(100);
                Tortuga.motorsConfiguration(stepper_motors_velocity, stepper_motors_acceleration);
                break;
            }
          }
          cubeFound = Tortuga.checkForCubeBack(table_height);

          if(cubeFound == 1){ // encontrou um cubo atrás, então pega
            Tortuga.moveForward(50);
            Tortuga.getCubeBack(table_height); //getcubeBack
            char cube_color = Tortuga.checkCubeColor();
            if (cube_color == 'B') { // mostra a cor do cubo
              rgbLED.blue();
              rgbLED.off();
            } else {
              rgbLED.red();
              rgbLED.off();
            }
            cube_counter++;

          }else{ // ir embora 
            while(1){
              int distanceFrente = usSensorFront.getDistance();
              Tortuga.moveRight(70);
              if(distanceFrente > 10){
                Tortuga.moveRight(500);
                break;
              }
            }
          }
          Tortuga.moveForward(2300);
          Tortuga.rotateClockwise(565);
        }

        Tortuga.moveForward(3300);
        Tortuga.rotateAntiClockwise(565);

        //anda ate a parede da mesa de entrega
        while(1){
          Tortuga.moveForward(150);
          int frontDistance = usSensorFront.getDistance();
          if(frontDistance <= 15){
            Tortuga.stop();
            Tortuga.rotateClockwise(565);
            break;
          }
        }
        
        while (true) { // anda ate encontrar a mesa de entrega
            Tortuga.moveForward(150);
            int front_distance = usSensorFront.getDistance();
            if (front_distance <= 5) { // se alinha com a mesa
                Tortuga.motorsConfiguration(300, 300);
                Tortuga.moveForward(100);
                Tortuga.motorsConfiguration(stepper_motors_velocity, stepper_motors_acceleration);
                break;
            }
        }

        int deliveryTableHeight;
        deliveryTableHeight = Tortuga.checkTableHeightFront();

        


    }
}

/*while(1){
            Tortuga.moveForward(120);
            int FrontDistance = usSensorFront.getDistance();
            if(FrontDistance <= 10){
              Tortuga.rotateClockwise(562);
              break;
            }
          }

          while (true) { // anda ate encontrar a mesa
            Tortuga.moveForward(150);
            int front_distance = usSensorFront.getDistance();
            if (front_distance <= 10) { // se alinha com a mesa
                Tortuga.motorsConfiguration(300, 300);
                Tortuga.moveForward(100);
                Tortuga.motorsConfiguration(stepper_motors_velocity, stepper_motors_acceleration);
                break;
            }
          }*/

          //int deliveryTableHeight = Tortuga.checkTableHeightFront();
          // soltar o cubo de acordo com a altura da mesa de delivery