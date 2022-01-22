// protects user from including library twice
#ifndef PlaneAnimation_h
#define PlaneAnimation_h

#include "Animation.h"

class PlaneAnimation:public Animation {
    public:
        void renderNextFrame();
        // Declare your own methods here
};
#endif
