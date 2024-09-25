#include "InfraredSensor.h"
#include <Arduino.h>

// Construtor da classe
InfraredSensor::InfraredSensor(int analog_pin, int digital_pin) {
    this->analog_pin = analog_pin;  // Armazena o pino analógico
    this->digital_pin = digital_pin;  // Armazena o pino digital
    pinMode(analog_pin, INPUT);     // Configura o pino analógico como entrada
    pinMode(digital_pin, INPUT);    // Configura o pino digital como entrada
}

// Função para medir a distância com base no pino analógico
int InfraredSensor::measureDistance() {
    int distance = analogRead(analog_pin);  // Lê o valor do pino analógico
    return distance;  // Retorna a distância medida
}

// Função para verificar proximidade com base no pino digital
bool InfraredSensor::checkNearby() {
    if (digitalRead(digital_pin) == LOW) {  // Se o pino digital for LOW, não há objeto perto
        return false;
    } else {  // Se o pino digital for HIGH, há um objeto perto
        return true;
    }
}
