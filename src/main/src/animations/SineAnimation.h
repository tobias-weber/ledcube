// protects user from including library twice
#ifndef SineAnimation_h
#define SineAnimation_h

#include "../Animation.h"

class SineAnimation:public Animation {
    private:
        float sineCounter = 0;
        float edge = PI * 3 / 5;
        byte sineColors[5] = {0b000011, 0b001111, 0b001100, 0b111100, 0b110000};
    public:
        void renderNextFrame();
        SineAnimation();
        float fmap(float x, float in_min, float in_max, float out_min, float out_max);
        // Declare your own methods here
};
#endif
