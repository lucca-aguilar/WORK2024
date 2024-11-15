#include <advanced-manipulation-test.h>
#include <Setup.h>

int find_tag(int tag_id) {
    int detected_tag = read_tag();
    while (detected_tag != tag_id) {
        int frontDistance = usSensorFront.getDistance();
        int rightDistance = usSensorRight.getDistance();
        if (frontDistance > 10 && rightDistance > 10) {
            Tortuga.moveLeft(70);
        } else {
            Tortuga.moveRight(70);
        }
    }
    Tortuga.alignWithTag();
}

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

void advancedManipulationTest() {
    // inicializa variáveis de contagem
    int tags_counter = 1;
    int cube_counter = 0;

    // coloca a garra na posição inicial
    Tortuga.defaultClawPosition();

    // anda até encontrar a mesa
    while(1) {
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
    }
    // checa a altura da mesa
    int table_height = Tortuga.checkTableHeightFront();

    // vai para o canto direito da mesa
    while(1) {
        int rightDistance = usSensorRight.getDistance();
        Tortuga.moveRight(70);
        if (rightDistance < 10) {
            Tortuga.stop();
        }
    }
    
    // começa a escanear as tags da direita para a esquerda e armazena os numeros em um array]
    int tags_ids[8];


    // ordena o array
    // volta para o canto direito e começa a procurar pela menor tag do array
    // quando encontra o menor cubo do array, começa a procurar por ele
    // se alinha e pega o cubo
    // aumenta o contador
    // vai para a parte de trás da mesa
    // coloca o cubo na devida posição, de acordo com o contador
    // se for o último, sai da arena e vai embora

    start();
}
