// protects user from including library twice
#ifndef FadingCube_h
#define FadingCube_h

#include "../Animation.h"

class FadingCube:public Animation {
    private:
        // Declare your class variables and your own methods here. 
        byte color = 0;
        byte colors[9];

        
        byte colorR[9];
        byte colorG[9];
        byte colorB[9];

    public:
        void renderNextFrame();
        FadingCube();
};
#endif
