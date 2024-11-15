#include <advanced-manipulation-test.h>
#include <Setup.h>

int read_tag() {
    // variável para armazenar o ID
    int tag = -1;  // valor inicial

    // envia comando para a Raspberry
    char comando = 'A';
    raspy.write(comando);
    delay(100);

    // verifica se há uma resposta do ID da tag
    if (raspy.available() > 0) {
        String tag_string = raspy.readStringUntil('\n');
        tag = tag_string.toInt();
        Serial.println("ID da AprilTag recebida: " + String(tag));
    }
}

int find_tag(int tag_id) {
    int detected_tag = read_tag();
    while (detected_tag != tag_id) {
        int frontDistance = usSensorFront.getDistance();
        int rightDistance = usSensorRight.getDistance();
        if (frontDistance <= 10) {
            Tortuga.moveLeft(70);
        } else {
            Tortuga.moveRight(70);
        }
    }
    Tortuga.alignWithTag();
}

int findDistance(int tags_counter) {
    int distance;
    if(tags_counter == 1) {
        distance = 700;
        return distance;
    }
    if (tags_counter == 2) {
        distance = 550;
        return distance;
    }
    if (tags_counter == 3) {
        distance = 400;
        return distance;
    }
    if (tags_counter == 4) {
        distance = 250;
        return distance;
    } if (tags_counter == 5) {
        distance = 100;
        return distance;
    }
}

void advancedManipulationTest() {
    // inicializa variáveis de contagem
    int tags_counter = 1;

    // coloca a garra na posição inicial
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
    
    // checa a altura da mesa
    int table_height = Tortuga.checkTableHeightFront();

    while(tags_counter <= 5) {
         // vai para o canto direito da mesa
        while(1) {
            int rightDistance = usSensorRight.getDistance();
            Tortuga.moveRight(70);
            Serial.print("USR =");
            Serial.println(rightDistance);
            if (rightDistance < 10) {
                Tortuga.stop();
                delay(10000);
                break;
            }
        }

        // encontra a tag correspondente
        find_tag(tags_counter);

        // pega o cubo
        Tortuga.getCubeFront(table_height);

        // vai para a parte de trás da mesa
        Tortuga.moveLeft(850);
        Tortuga.moveForward(1800);
        Tortuga.rotateClockwise(1110);
        while(1) {
            int frontDistance = usSensorFront.getDistance();
            Tortuga.moveLeft(70);
            if (frontDistance < 10) {
                break;
            }
        }

        // coloca o cubo de acordo com sua distancia correta
        int distance = findDistance(tags_counter);
        Tortuga.moveLeft(distance);
        Tortuga.placeCube(20);
        tags_counter++;

        // volta para a mesa da frente
        Tortuga.moveRight(distance + 100);
        Tortuga.moveForward(1800);
        Tortuga.rotateClockwise(1110);
        while(1) {
            int frontDistance = usSensorFront.getDistance();
            Tortuga.moveRight(70);
            if (frontDistance < 10) {
                break;
            }
        }
    }

    Tortuga.moveLeft(70);
    Tortuga.moveBackward(100);
    Tortuga.rotateAntiClockwise(562);
    Tortuga.moveLeft(500);
    Tortuga.moveForward(3500);
    Tortuga.rotateAntiClockwise(562);
    Tortuga.moveForward(1000);

}
