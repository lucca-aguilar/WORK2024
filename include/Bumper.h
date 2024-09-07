#ifndef BUMPER_H
#define BUMPER_H

class Bumper {
public:
    Bumper(int pin);
    bool checkCube();
    
private:
    int _pin;
};

#endif