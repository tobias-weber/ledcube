// protects user from including library twice
#ifndef ScreenSaver_h
#define ScreenSaver_h

#include "../Animation.h"

class ScreenSaver:public Animation {
    private:
        int x_pos = 0;
        int y_pos = 1;
        int z_pos = 2;

        int x_change = 1;
        int y_change = 1;
        int z_change = 1;

        byte screenSaverColor = 0;
        byte screenSaverColors[7] = {0b000001, 0b000100, 0b000101, 0b010000, 0b010001, 0b010100, 0b010101};

    public:
        void renderNextFrame();
        int newDirection(int oldDirection);
        int limit(int coord);
        ScreenSaver();
};
#endif
