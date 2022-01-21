// protects user from including library twice
#ifndef ScreenSaver_h
#define ScreenSaver_h

#include "Animation.h"

class ScreenSaver:public Animation {
    public:
        void renderNextFrame();
};
#endif
