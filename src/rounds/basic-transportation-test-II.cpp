#include <basic-transportation-test-II.h>
#include <Setup.h>
#define RED_CONTEINER_TAG
#define BLUE_CONTEINER_TAG
#define STACKING_TAG
#define SHELF_TAG
#define PRECISION_TABLE_TAG

void basicTransportationTestII() {
    // define variáveis globais
    int cube_counter;
    int cube_id;

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

        // encontra o cubo, armazena a tag e se alinha com ele 
        cube_id = Tortuga.checkForCubeVision();
    }

    // ir até a mesa
    // se alinhar
    // verificar altura da mesa
    // procurar por cubos usando a visão
    // se encontrar um cubo
        // le a tag
        // se alinha com a tag
        // pega
        // aumenta o contador
        // vai para a linha
    // se não encontrar um cubo
        // vai embora
    // contador == 5
        // vai embora
    // tag = red conteiner
    // tag = blue conteiner
    // tag = stacking
    // tag = shelf
    // tag = precision table

    start();
}