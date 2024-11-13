#include <basic-manipulation-test.h>
#include <Setup.h>

void basicManipulationTest() {
    // declara algumas variaveis globais
    int cube_counter = 0;
    char cube_color;
    Serial.println("Entrou na função");

    while(1) {
        // coloca a garra nas posicoes corretas
        Tortuga.defaultClawPosition();
        Serial.println("garra inicial");

        while(1) { // anda ate encontrar a mesa
            Tortuga.moveForward(150);
            int front_distance = usSensorFront.getDistance();
            if (front_distance <= 5) { // se alinha com a mesa
                Tortuga.motorsConfiguration(300, 300);
                Tortuga.moveForward(30);
                Tortuga.motorsConfiguration(stepper_motors_velocity, stepper_motors_acceleration);
                break;
            }
        }
        Serial.println("Encontrou a mesa");

        // verifica altura da mesa
        int table_height = Tortuga.checkTableHeightFront();
        Serial.println(table_height);

        // escaneia em busca de um cubo pela frente
        int cubeFound = Tortuga.checkForCubeFront(table_height);
        Serial.println("Cubefound is " + cubeFound);

        if(cubeFound == 1){ // pega o cubo, caso encontre na frente
          Tortuga.getCubeFront(table_height); //confirmacao que pegou o cubo
          cube_color = Tortuga.checkCubeColor();
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
          Tortuga.rotateClockwise(1110);
          Tortuga.moveLeft(850);

          while (1) { // anda ate encontrar a mesa
            Tortuga.moveForward(150);
            int front_distance = usSensorFront.getDistance();
            if (front_distance <= 5) { // se alinha com a mesa
                Tortuga.motorsConfiguration(300, 300);
                Tortuga.moveForward(30);
                Tortuga.motorsConfiguration(stepper_motors_velocity, stepper_motors_acceleration);
                break;
            }
          }
          int cubeFound = Tortuga.checkForCubeBack(table_height);

          if(cubeFound == 1){ // encontrou um cubo atrás, então pega
            Tortuga.moveForward(50);
            Tortuga.getCubeBack(table_height); //getcubeBack
            cube_color = Tortuga.checkCubeColor();
            if (cube_color == 'B') { // mostra a cor do cubo
              rgbLED.blue();
              rgbLED.off();
            } else {
              rgbLED.red();
              rgbLED.off();
            }
            cube_counter++;

          }else{ // ir embora para finish
            while(1){
              int distanceFrente = usSensorFront.getDistance();
              Tortuga.moveRight(70);
              if(distanceFrente > 10){
                Tortuga.moveRight(500);
                break;
              }
            }

            Tortuga.moveForward(2400);
            Tortuga.rotateClockwise(562);
            Tortuga.moveForward(4500);
            Tortuga.rotateAntiClockwise(562);
            Tortuga.moveForward(1200);
            Tortuga.stop();
            delay(15000);
          }
          Tortuga.moveForward(2400);
          Tortuga.rotateClockwise(560);
        }

        Tortuga.moveForward(3300);
        Tortuga.rotateAntiClockwise(30);

        //anda ate a parede da mesa de entrega
        while(1){
          Tortuga.moveLeft(1500);
          int leftDistance = usSensorLeft.getDistance();
          if(leftDistance <= 25){
            Tortuga.stop();
            break;
          }
        }
        
        while (1) { // anda ate encontrar a mesa de entrega
            Tortuga.moveForward(150);
            int front_distance = usSensorFront.getDistance();
            if (front_distance <= 5) { // se alinha com a mesa
                Tortuga.motorsConfiguration(300, 300);
                Tortuga.moveForward(30);
                Tortuga.motorsConfiguration(stepper_motors_velocity, stepper_motors_acceleration);
                break;
            }
        }

        // ir para direita da mesa de entrega
        while(1){
          int FrontDistance = usSensorFront.getDistance();
          Tortuga.moveRight(70);
          if(FrontDistance > 20){
            Tortuga.stop();
            break;
          }
        }

        //checa a mesa de conteiner e coloca o cubo no conteiner
        while(1){
          int leftDistance = usSensorLeft.getDistance();
          int containerdistance = irSensorTableHeight2.measureDistance();
          Tortuga.moveLeft(70);
          if(containerdistance < 950){
            char conteiner = Tortuga.checkConteinerColor();
            if(conteiner == cube_color){
              Tortuga.placeCube(20);
              while(1){
                Tortuga.moveRight(70);
                int frontdistance = usSensorFront.getDistance();
                if(frontdistance > 15){
                  delay(15000);
                  break;
                }
              }
              break;
            }
          }
          if(leftDistance <= 10){
            while(1){
                int frontdistancetable = usSensorFront.getDistance();
                Tortuga.moveRight(70);
                int frontdistanceconteiner = irSensorTableHeight2.measureDistance();
                if(frontdistanceconteiner < 950){
                  Tortuga.stop();
                  char conteiner = Tortuga.checkConteinerColor();
                  if(conteiner == cube_color){
                    Tortuga.placeCube(20);
                    while(1){
                      Tortuga.moveRight(70);
                      int frontdistance = usSensorFront.getDistance();
                      if(frontdistance > 15){
                        break;
                      }
                    }
                  }
                }
                if(frontdistancetable > 15){
                  Tortuga.moveRight(500);
                  Tortuga.moveForward(2000);
                  Tortuga.rotateAntiClockwise(562);
                  Tortuga.moveForward(1500);
                  Tortuga.stop();
                  delay(15000);
                }
            }
        }

    }
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