// protects user from including library twice
#ifndef ExpandingSphereAnimation_h
#define ExpandingSphereAnimation_h

#include "Animation.h"

class ExpandingSphereAnimation:public Animation {
    public:
        void renderNextFrame();
        void initialize();
        // Declare your own methods here
};
#endif
