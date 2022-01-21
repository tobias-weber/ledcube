// protects user from including library twice
#ifndef ExampleAnimation_h
#define ExampleAnimation_h

#include "Animation.h"

class ExampleAnimation:public Animation {
    public:
        void renderNextFrame();
        // Declare your own methods here
};
#endif
