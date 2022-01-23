// protects user from including library twice
#ifndef TemplateAnimation_h
#define TemplateAnimation_h

#include "Animation.h"

class TemplateAnimation:public Animation {
    public:
        void renderNextFrame();
        void initialize();
        // Declare your own methods here
};
#endif
