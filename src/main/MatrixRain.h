// protects user from including library twice
#ifndef MatrixRain_h
#define MatrixRain_h

#include "Animation.h"

class MatrixRain:public Animation {
    public:
        void renderNextFrame();
        void initialize();
        // Declare your own methods here
};
#endif
