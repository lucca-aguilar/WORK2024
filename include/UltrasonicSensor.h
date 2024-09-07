#ifndef ULTRASONIC_SENSOR_H
#define ULTRASONIC_SENSOR_H

class UltrasonicSensor {
public:
    UltrasonicSensor(int triggerPin, int echoPin);
    long measureDistance();
    
private:
    int _triggerPin;
    int _echoPin;
};

#endif