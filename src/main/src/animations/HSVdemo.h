// protects user from including library twice
#ifndef HSVdemo_h
#define HSVdemo_h

#include "../Animation.h"

class HSVdemo:public Animation {
    private:
        // Declare your class variables and your own methods here. 
        int hue = 0;
        byte counter = 0;

        byte velocities[5] = {90, 60, 40, 25, 10};
        
        int joyYPin;
        int joyXPin;
        int btnXPin;
        int btnYPin;
        
        byte joyXnumOfRanges = 5;
        int joyXRanges[4] = {150, 300, 400, 550}; // Define Borders of Ranges. Must have length numOfRanges - 1

        byte joyYnumOfRanges = 5;
        int joyYRanges[4] = {180, 305, 430, 555}; // Define Borders of Ranges. Must have length numOfRanges - 1
        int getCalibratedY();
        bool isBtnYReleased();
        bool isBtnXReleased();
        bool btnXPressed = false;
        bool btnYPressed = false;
    public:
        void renderNextFrame();
        HSVdemo();
};
#endif
