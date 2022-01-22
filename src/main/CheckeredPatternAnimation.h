// protects user from including library twice
#ifndef CheckeredPatternAnimation_h
#define CheckeredPatternAnimation_h

#include "Animation.h"

class CheckeredPatternAnimation:public Animation {
    public:
        void renderNextFrame();
        // Declare your own methods here
};
#endif
