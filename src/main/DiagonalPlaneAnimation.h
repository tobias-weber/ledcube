// protects user from including library twice
#ifndef DiagonalPlaneAnimation_h
#define DiagonalPlaneAnimation_h

#include "Animation.h"

class DiagonalPlaneAnimation:public Animation {
    private:
        byte dpCounter = 0;
        boolean dpFlip = false;
    public:
        void renderNextFrame();
        DiagonalPlaneAnimation();
        // Declare your own methods here
};
#endif
