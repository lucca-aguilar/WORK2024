#include "Bumper.h"
#include <Arduino.h>

Bumper::Bumper(int pin) : pin(pin) {
    pinMode(pin, INPUT);  // Configura o pino do bumper como entrada
}

int Bumper::checkCube() {
    if (digitalRead(pin) == HIGH) {
        return 0;
    } else {
        return 1;
    } 
}
