// protects user from including library twice
#ifndef TextAnimation_h
#define TextAnimation_h

#include "Animation.h"

class TextAnimation:public Animation {
    public:
        void renderNextFrame();
        // Declare your own methods here
};
#endif
