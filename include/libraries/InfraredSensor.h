#ifndef INFRARED_SENSOR_H
#define INFRARED_SENSOR_H

#include <Arduino.h>

class InfraredSensor {
  public:
    InfraredSensor(int analog_pin, int digital_pin);  // Construtor
    int measureDistance();        // Método para medir a distância
    bool checkNearby();           // Método para verificar proximidade

  private:
    int analog_pin;  // Pino analógico
    int digital_pin; // Pino digital
};

#endif
