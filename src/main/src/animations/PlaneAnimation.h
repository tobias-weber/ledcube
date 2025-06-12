// protects user from including library twice
#ifndef PlaneAnimation_h
#define PlaneAnimation_h

#include "../Animation.h"

class PlaneAnimation:public Animation {
    private:
        byte state = 0;
        byte layer = 0;
    public:
        void renderNextFrame();
        PlaneAnimation();
        // Declare your own methods here
};
#endif
