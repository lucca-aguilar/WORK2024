#ifndef VISION_H
#define VISION_H

class Vision {
public:
    Vision(int rx, int tx);
    void startCamera();
    int readTag();
    bool checkWall();
    
private:
    int _pin;
};

#endif