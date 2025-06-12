// protects user from including library twice
#ifndef CheckeredPatternAnimation_h
#define CheckeredPatternAnimation_h

#include "../Animation.h"

class CheckeredPatternAnimation:public Animation {
    private:
        // Declare your own variables here
        byte cpFrame = 0;
    public:
        CheckeredPatternAnimation();
        void renderNextFrame();
        // Declare your own methods here
};
#endif
