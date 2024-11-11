#include <Arduino.h>
#include "LED.h"

LED::LED(int blue_pin, int red_pin) : blue_pin(blue_pin), red_pin(red_pin) {
    pinMode(red_pin, OUTPUT);
    pinMode(blue_pin, OUTPUT);
} 

void LED::blue() {
    digitalWrite(blue_pin, HIGH);
    delay(3000);
}

void LED::red() {
    digitalWrite(red_pin, HIGH);
    delay(3000);
}

void LED::off() {
    digitalWrite(blue_pin, LOW);
    digitalWrite(red_pin, LOW);
}