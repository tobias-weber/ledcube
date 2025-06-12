// protects user from including library twice
#ifndef RandomColorsAnimation_h
#define RandomColorsAnimation_h

#include "../Animation.h"

class RandomColorsAnimation:public Animation {
    private:
        byte rcColors[7] = {0b000001, 0b010000, 0b000100, 0b010100, 0b010001, 0b000101, 0b010101};
        byte rcFrame = 0;
        byte rcLayerPos = 0;
        byte rcLayerAxis = 0;
        byte rcLayerColor = 1;
        byte rcStart = 4;
    public:
        void renderNextFrame();
        RandomColorsAnimation();
        // Declare your own methods here
};
#endif
