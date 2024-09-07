#include "InfraredSensor.h"
#include <Arduino.h>

InfraredSensor::InfraredSensor(int pin) : _pin(pin) {
    pinMode(_pin, INPUT);
}

int InfraredSensor::measureDistance() {
    int distance = analogRead(_pin);
    return distance;
}

bool InfraredSensor::checkNearby() {
    bool detection;
    if (digitalRead(_pin) == 0) {
        detection = false;
    }
}