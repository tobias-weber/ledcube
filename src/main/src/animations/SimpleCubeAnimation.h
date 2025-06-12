// protects user from including library twice
#ifndef SimpleCubeAnimation_h
#define SimpleCubeAnimation_h

#include "../Animation.h"

class SimpleCubeAnimation:public Animation {
    private:
        int counter = 0;
        byte colorsTable[21] = {0b000001, 0, 0, 0b000100, 0, 0, 0b000101, 0, 0, 0b010000, 0, 0, 0b010001, 0, 0, 0b010100, 0, 0, 0b010101, 0, 0};
        byte colorsTableSize = 21;
    public:
        void renderNextFrame();
        SimpleCubeAnimation();
        // Declare your own methods here
};
#endif
