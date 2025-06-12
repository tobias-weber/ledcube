// protects user from including library twice
#ifndef MatrixRain_h
#define MatrixRain_h

#include "../Animation.h"

class MatrixRain:public Animation {
    private:
        byte spawn = 125;
        byte spawnProbability = 100;
    public:
        void renderNextFrame();
        MatrixRain();
        // Declare your own methods here
};
#endif
