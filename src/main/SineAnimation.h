// protects user from including library twice
#ifndef SineAnimation_h
#define SineAnimation_h

#include "Animation.h"

class SineAnimation:public Animation {
    public:
        void renderNextFrame();
        void initialize();
        float fmap(float x, float in_min, float in_max, float out_min, float out_max);
        // Declare your own methods here
};
#endif
