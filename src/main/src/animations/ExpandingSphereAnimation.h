// protects user from including library twice
#ifndef ExpandingSphereAnimation_h
#define ExpandingSphereAnimation_h

#include "../Animation.h"

class ExpandingSphereAnimation:public Animation {
    private:
        int esCounter = 1;
        byte esSize = 1;
        byte esTargetSize = 4;
        int esDirection = 1;
        byte esColor = 0;
        byte esInnerColor = 0;
        byte esColors[6] = {0b000001, 0b010000, 0b010100, 0b010001, 0b000101, 0b010101};
    public:
        void renderNextFrame();
        ExpandingSphereAnimation();
        // Declare your own methods here
};
#endif
