// protects user from including library twice
#ifndef TextExampleAnimation_h
#define TextExampleAnimation_h

#include "Animation.h"

class TextExampleAnimation:public Animation {
    public:
        void renderNextFrame();
        // Declare your own methods here
};
#endif
