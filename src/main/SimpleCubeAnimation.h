// protects user from including library twice
#ifndef SimpleCubeAnimation_h
#define SimpleCubeAnimation_h

#include "Animation.h"

class SimpleCubeAnimation:public Animation {
    public:
        void renderNextFrame();
        void initialize();
        // Declare your own methods here
};
#endif
