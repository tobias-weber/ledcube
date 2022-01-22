// protects user from including library twice
#ifndef RandomColorsAnimation_h
#define RandomColorsAnimation_h

#include "Animation.h"

class RandomColorsAnimation:public Animation {
    public:
        void renderNextFrame();
        // Declare your own methods here
};
#endif
