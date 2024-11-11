#ifndef LED_H
#define LED_H

class LED {
public:
    LED(int blue_pin, int red_pin);
    void blue();
    void red();
    void off();
    
private:
    int blue_pin;
    int red_pin;
};

#endif