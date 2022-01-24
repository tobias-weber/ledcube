// protects user from including library twice
#ifndef DiagonalPlaneAnimation_h
#define DiagonalPlaneAnimation_h

#include "Animation.h"

class DiagonalPlaneAnimation:public Animation {
    public:
        void renderNextFrame();
        void initialize();
        // Declare your own methods here
};
#endif
