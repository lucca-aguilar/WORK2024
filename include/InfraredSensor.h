#ifndef INFRARED_SENSOR_H
#define INFRARED_SENSOR_H

class InfraredSensor {
public:
    InfraredSensor(int pin);
    int measureDistance(); 
    bool checkNearby(); 
    
private:
    int _pin;
};

#endif