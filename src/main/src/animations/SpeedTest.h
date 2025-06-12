// protects user from including library twice
#ifndef SpeedTest_h
#define SpeedTest_h

#include "../Animation.h"

class SpeedTest:public Animation {
    private:
        // Declare your class variables and your own methods here. 
        byte color;
        byte index;
        byte colors[7] = {0b000011, 0b110000, 0b001100, 0b111100, 0b110011, 0b001111, 0b111111};
        long counter;
        byte state = 0;
        int runTime = 2000; // in millis
        unsigned long startTime;
        byte digits[4] = {0,0,0,0};
        int displayTime = 1000; // time per digit in millis
        
        int btnXPin = A3;
        bool isBtnXReleased();
        bool btnXPressed = false;

    public:
        void renderNextFrame();
        SpeedTest();
};
#endif
