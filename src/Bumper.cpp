#include "Bumper.h"
#include <Arduino.h>

Bumper::Bumper(int pin) : pin(pin) {
    pinMode(pin, INPUT);  // Configura o pino do bumper como entrada
}

bool Bumper::checkCube() {
    return digitalRead(pin) == HIGH;  // Retorna true se o bumper detectar um cubo
}
