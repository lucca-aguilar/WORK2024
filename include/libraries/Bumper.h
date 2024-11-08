#ifndef BUMPER_H
#define BUMPER_H

class Bumper {
public:
    Bumper(int pin);
    int checkCube();
    
private:
    int pin;
};

#endif