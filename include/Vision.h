#ifndef CAMERA_H
#define CAMERA_H

class Camera {
public:
    Camera(int triggerPin, int echoPin);
    void startCamera();
    int readTag();
    bool checkWall();
    
private:
    int _pin;
};

#endif