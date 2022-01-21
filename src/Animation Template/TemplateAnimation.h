// protects user from including library twice
#ifndef TemplateAnimation_h
#define TemplateAnimation_h

#include "Animation.h"

class TemplateAnimation:public Animation {
    public:
        void renderNextFrame();
        // Declare your own methods here
};
#endif
