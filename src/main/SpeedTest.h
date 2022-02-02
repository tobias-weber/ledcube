// protects user from including library twice
#ifndef SpeedTest_h
#define SpeedTest_h

#include "Animation.h"

class SpeedTest:public Animation {
    private:
        // Declare your class variables and your own methods here. 
        byte color = 0;
        byte index = 0;
        byte colors[7] = {0b000001, 0b010000, 0b000100, 0b010100, 0b010001, 0b000101, 0b010101};
    public:
        void renderNextFrame();
        SpeedTest();
};
#endif
