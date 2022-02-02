// protects user from including library twice
#ifndef SineAnimation_h
#define SineAnimation_h

#include "Animation.h"

class SineAnimation:public Animation {
    private:
        float sineCounter = 0;
        float edge = PI * 3 / 5;
        byte sineColors[5] = {0b000001, 0b000101, 0b000100, 0b010100, 0b010000};
    public:
        void renderNextFrame();
        SineAnimation();
        float fmap(float x, float in_min, float in_max, float out_min, float out_max);
        // Declare your own methods here
};
#endif
